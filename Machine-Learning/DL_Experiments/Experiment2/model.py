import random
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.nn.utils.rnn import pack_padded_sequence, pad_packed_sequence


class Encoder(nn.Module):
    def __init__(self, input_dim, emb_dim, enc_hid_dim, dec_hid_dim, dropout):
        super().__init__()
        self.embedding = nn.Embedding(input_dim, emb_dim)
        self.rnn = nn.GRU(emb_dim, enc_hid_dim, bidirectional=True)
        self.fc = nn.Linear(enc_hid_dim * 2, dec_hid_dim)
        self.dropout = nn.Dropout(dropout)

    def forward(self, src, src_len):
        # src = [src_len, bsz]
        # src_len = [bsz]
        # embedded = [src_len, bsz, emb_dim]
        embedded = self.embedding(src)

        # pack_padded_sequence -> need to explicitly put lengths on cpu!
        packed_embedded = pack_padded_sequence(embedded, src_len.to('cpu'))

        # packed_outputs is a packed sequence containing all hidden states
        # hidden is now from the final non-padded element in the batch
        packed_outputs, hidden = self.rnn(packed_embedded)

        # pad_packed_sequence
        # outputs is now a non-packed sequence, all hidden states obtained when the input is a pad token are all zeros
        # outputs = [src_len, bsz, enc_hid_dim * num_directions]
        # hidden = [n_layers * num_directions, bsz, enc_hid_dim]
        outputs, _ = pad_packed_sequence(packed_outputs)

        # hidden is stacked [forward_1, backward_1, forward_2, backward_2, ...]
        # outputs are always from the last layer

        # hidden [-2, :, : ] is the last of the forwards RNN -> [bsz, enc_hid_dim]
        # hidden [-1, :, : ] is the last of the backwards RNN -> [bsz, enc_hid_dim]

        # initial decoder hidden is final hidden state of the forwards and backwards
        #  encoder RNNs fed through a linear layer
        hidden = torch.tanh(self.fc(torch.cat((hidden[-2, :, :], hidden[-1, :, :]), dim=1)))

        # outputs = [src_len, bsz, enc_hid_dim * 2]
        # hidden = [bsz, dec_hid_dim]
        return outputs, hidden


class Attention(nn.Module):
    def __init__(self, enc_hid_dim, dec_hid_dim):
        super().__init__()
        self.attn = nn.Linear((enc_hid_dim * 2) + dec_hid_dim, dec_hid_dim)
        self.v = nn.Linear(dec_hid_dim, 1, bias=False)

    def forward(self, hidden, encoder_outputs, mask):
        # hidden = [bsz, dec_hid_dim]
        # encoder_outputs = [src_len, bsz, enc_hid_dim * 2]
        batch_size = encoder_outputs.shape[1]
        src_len = encoder_outputs.shape[0]

        # repeat decoder hidden state src_len times
        # hidden = [bsz, dec_hid_dim] -> [bsz, src_len, dec_hid_dim]
        hidden = hidden.unsqueeze(1).repeat(1, src_len, 1)

        # encoder_outputs = [src_len, bsz, enc_hid_dim * 2] -> [bsz, src_len, enc_hid_dim * 2]
        encoder_outputs = encoder_outputs.permute(1, 0, 2)

        # torch.cat((hidden, encoder_outputs), dim=2) = [bsz, src_len, enc_hid_dim * 2 + dec_hid_dim]
        # energy = [bsz, src_len, dec_hid_dim]
        energy = torch.tanh(self.attn(torch.cat((hidden, encoder_outputs), dim=2)))

        # self.v(energy) = [bsz, src_len, 1]
        # attention = [bsz, src_len]
        attention = self.v(energy).squeeze(2)

        # mask & softmax
        attention = attention.masked_fill(mask == 0, -1e10)
        return F.softmax(attention, dim=1)


class Decoder(nn.Module):
    def __init__(self, output_dim, emb_dim, enc_hid_dim, dec_hid_dim, dropout, attention):
        super().__init__()
        self.output_dim = output_dim
        self.attention = attention
        self.embedding = nn.Embedding(output_dim, emb_dim)
        self.rnn = nn.GRU((enc_hid_dim * 2) + emb_dim, dec_hid_dim)
        self.fc_out = nn.Linear((enc_hid_dim * 2) + dec_hid_dim + emb_dim, output_dim)
        self.dropout = nn.Dropout(dropout)

    def forward(self, input, hidden, encoder_outputs, mask):
        # input = [bsz]
        # hidden = [bsz, dec_hid_dim]
        # encoder_outputs = [src_len, bsz, enc_hid_dim * 2]
        # mask = [bsz, src_len]

        # input = [1, bsz]
        input = input.unsqueeze(0)
        # embedded = [1, bsz, emb_dim]
        embedded = self.dropout(self.embedding(input))

        # a = [bsz, src_len], 第二维每一行加起来和为1
        a = self.attention(hidden, encoder_outputs, mask)
        # a = [bsz, src_len] -> [bsz, 1, src_len]
        a = a.unsqueeze(1)

        # encoder_outputs = [src_len, bsz, enc_hid_dim * 2] -> [bsz, src_len, enc_hid_dim * 2]
        encoder_outputs = encoder_outputs.permute(1, 0, 2)
        # weighted = [bsz, 1, enc_hid_dim * 2]
        weighted = torch.bmm(a, encoder_outputs)
        # weighted = [bsz, 1, enc_hid_dim * 2] -> [1, bsz, enc_hid_dim * 2]
        weighted = weighted.permute(1, 0, 2)

        # rnn_input = [1, bsz, emb_dim + (enc_hid_dim * 2)]
        rnn_input = torch.cat((embedded, weighted), dim=2)

        # output = [seq_len, bsz, dec_hid_dim * n_directions], 这里seq_len是1
        # hidden = [n_layers * n_directions, bsz, dec_hid_dim], 这里n_layers * n_directions是1*1=1
        # 也就是↓
        # seq_len, n layers and n directions will always be 1 in this decoder, therefore:
        # output = [1, bsz, dec_hid_dim]
        # hidden = [1, bsz, dec_hid_dim]
        output, hidden = self.rnn(rnn_input, hidden.unsqueeze(0))

        # this also means that output == hidden, 因为一层，一个方向，序列长度也为1
        assert (output == hidden).all()

        # embedded = [1, bsz, emb_dim] -> [bsz, emb_dim]
        embedded = embedded.squeeze(0)
        # output = [1, bsz, dec_hid_dim] -> [bsz, dec_hid_dim]
        output = output.squeeze(0)
        # weighted = [1, bsz, enc_hid_dim * 2] -> [bsz, enc_hid_dim * 2]
        weighted = weighted.squeeze(0)

        # prediction = [bsz, output_dim]
        prediction = self.fc_out(torch.cat((output, weighted, embedded), dim=1))

        # hidden.squeeze(0) = [bsz, dec_hid_dim]
        # a.squeeze(1) = [bsz, src_len]
        return prediction, hidden.squeeze(0), a.squeeze(1)


class Seq2Seq(nn.Module):
    def __init__(self, encoder, decoder, src_pad_idx, device):
        super().__init__()
        self.encoder = encoder
        self.decoder = decoder
        self.src_pad_idx = src_pad_idx
        self.device = device

    def create_mask(self, src):
        mask = (src != self.src_pad_idx).permute(1, 0)
        return mask

    def forward(self, src, src_len, trg, teacher_forcing_ratio=0.5):
        # src = [src_len, bsz]
        # src_len = [bsz]
        # trg = [trg_len, bsz]

        batch_size = src.shape[1]
        trg_len = trg.shape[0]
        trg_vocab_size = self.decoder.output_dim

        # tensor to store decoder outputs
        outputs = torch.zeros(trg_len-1, batch_size, trg_vocab_size).to(self.device)#<sos>

        # encoder_outputs is all hidden states of the input sequence, back and forwards
        # hidden is the final forward and backward hidden states, passed through a linear layer
        # encoder_outputs = [src_len, bsz, enc_hid_dim * 2]
        # hidden = [bsz, dec_hid_dim]
        encoder_outputs, hidden = self.encoder(src, src_len)

        # first input to the decoder is the <sos> tokens
        input = trg[0, :]

        # mask = [bsz, src_len], mask矩阵的样子↓
        # tensor([[ True,  True,  True,  ...,  True,  True,  True],
        #         [ True,  True,  True,  ..., False, False, False],
        #         [ True,  True,  True,  ..., False, False, False],
        #         ...,
        #         [ True,  True,  True,  ..., False, False, False],
        #         [ True,  True,  True,  ..., False, False, False],
        #         [ True,  True,  True,  ..., False, False, False]], device='cuda:0')
        mask = self.create_mask(src)

        for t in range(trg_len-1):
            # insert input token embedding, previous hidden state, all encoder hidden states and mask 
            # receive output tensor (predictions) and new hidden state
            output, hidden, _ = self.decoder(input, hidden, encoder_outputs, mask)

            # outputs = [trg_len, batch_size, trg_vocab_size]
            # place predictions in a tensor holding predictions for each token
            outputs[t] = output

            # decide if we are going to use teacher forcing or not
            teacher_force = random.random() < teacher_forcing_ratio

            # get the highest predicted token from our predictions
            top1 = output.argmax(1)

            # if teacher forcing, use actual next token as next input
            # if not, use predicted token
            input = trg[t+1] if teacher_force else top1

        return outputs
