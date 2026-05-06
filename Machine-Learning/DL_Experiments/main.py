import os
import torch
import torch.nn as nn
import torch.optim as optim
import math
import time
import argparse
from torch.utils.data import DataLoader
from dataloader import RestaurantDataset
from config import Config
from nltk.tokenize import word_tokenize
from torch.nn.utils.rnn import pad_sequence
from model import Encoder, Decoder, Attention, Seq2Seq


os.environ["CUDA_VISIBLE_DEVICES"] = "0"

# 实验题05-01：数据预处理，表格数据 → 文本化 → 分词 → 添加<sos>/<eos> → 转ID → 填充对齐
def transfer_to_ids(t, mode, default_value):
    # src
    if mode == 0:
        # 遍历每个token，从src_vocab中获取ID，找不到则用default_value
        ids = [src_vocab.get(token, default_value) for token in t]
    # trg
    else:
        # 遍历每个token，从trg_vocab中获取ID，找不到则用default_value
        ids = [trg_vocab.get(token, default_value) for token in t]

    ids = torch.tensor(ids)# 转换为张量
    return ids


def convert_to_features(batch):
    # 1.get batch and tokenize
    table_batch = [s[0] for s in batch]
    reference_batch = [s[1] for s in batch]

    # 2.分词并添加特殊标记 <sos>（开始）和 <eos>（结束）,word_tokenize(t) 负责将原始文本拆分为单词列表
    table_tokens = [['<sos>'] + word_tokenize(t) + ['<eos>'] for t in table_batch]
    reference_tokens = [['<sos>'] + word_tokenize(t) + ['<eos>'] for t in reference_batch]


    # 3.order by the length of table
    sorted_idx = sorted(range(len(table_tokens)), key=lambda x: len(table_tokens[x]), reverse=True)
    ordered_table_tokens = [table_tokens[i] for i in sorted_idx]
    ordered_reference_tokens = [reference_tokens[i] for i in sorted_idx]

    # 4.get table_length & reference_length (type:tensor)
    table_length = torch.tensor([len(t) for t in ordered_table_tokens])
    reference_length = torch.tensor([len(t) for t in ordered_reference_tokens])

    # 5.convert to id sequence (type: tensor)
    table_ids = [transfer_to_ids(t, 0, cfg.unk_token_id) for t in ordered_table_tokens]
    reference_ids = [transfer_to_ids(t, 1, cfg.unk_token_id) for t in ordered_reference_tokens]

    # 6.对变长序列进行填充，使同一batch内长度一致
    # （______）_ids - 要填充的序列列表， batch_first - 批次维度的位置,padding_value - 填充值cfg.pad_token_id
    table_tensor = pad_sequence(table_ids, batch_first=True, padding_value=cfg.pad_token_id)
    reference_tensor = pad_sequence(reference_ids, batch_first=True, padding_value=cfg.pad_token_id)

    # 7.form batch tensors
    encodings = {
        'input_ids': table_tensor.transpose(1, 0).contiguous(),
        'input_len': table_length,
        'decoder_input_ids': reference_tensor.transpose(1, 0).contiguous(),
        'decoder_input_len': reference_length
    }

    return encodings


def epoch_time(start_time, end_time):
    elapsed_time = end_time - start_time
    elapsed_mins = int(elapsed_time / 60)
    elapsed_secs = int(elapsed_time - (elapsed_mins * 60))
    return elapsed_mins, elapsed_secs


def train(model, dataloader, optimizer, criterion, teacher_forcing_ratio):
    model.train()
    epoch_loss = 0
    for i, batch in enumerate(dataloader):
        optimizer.zero_grad()
        # 1.get output
        # src = [src_seq_len, bsz], src_len = [bsz], trg = [trg_seq_len, bsz]
        src = batch['input_ids'].to(cfg.device)
        src_len = batch['input_len'].to(cfg.device)
        trg = batch['decoder_input_ids'].to(cfg.device)

        # output = [trg_seq_len-1, bsz, output_dim]
        output = model(
            src=src,
            src_len=src_len,
            trg=trg,
            teacher_forcing_ratio=teacher_forcing_ratio
        )

        # 2.calculate the loss
        output_dim = output.shape[-1]

        output = output.view(-1, output_dim)
        trg = trg[1:].view(-1)

        # trg = [(trg_seq_len - 1) * bsz]
        # output = [(trg_seq_len - 1) * bsz, output_dim]
        loss = criterion(output, trg)

        # 3. loss backward
        loss.backward()
        optimizer.step()

        # 4. accumulate the loss
        epoch_loss += loss.item()

    return epoch_loss / len(dataloader)


def evaluate(model, dataloader, criterion):
    model.eval()
    epoch_loss = 0
    with torch.no_grad():
        for i, batch in enumerate(dataloader):
            # 1.get output
            # src = [src_seq_len, bsz], src_len = [bsz], trg = [trg_seq_len, bsz]
            src = batch['input_ids'].to(cfg.device)
            src_len = batch['input_len'].to(cfg.device)
            trg = batch['decoder_input_ids'].to(cfg.device)

            # output = [trg_seq_len-1, bsz, output_dim]
            output = model(
                src=src,
                src_len=src_len,
                trg=trg,
                teacher_forcing_ratio=0     # disable teacher forcing
            )

            # 2.calculate the loss
            output_dim = output.shape[-1]
            output = output.view(-1, output_dim)
            trg = trg[1:].view(-1)

            # trg = [(trg_seq_len - 1) * bsz]
            # output = [(trg_seq_len - 1) * bsz, output_dim]
            loss = criterion(output, trg)

            # 3. accumulate the loss
            epoch_loss += loss.item()

    return epoch_loss / len(dataloader)


def main():
    # 数据加载
    train_set = RestaurantDataset(mode='train')
    train_loader = DataLoader(
        train_set,
        batch_size=cfg.batch_size,
        shuffle=True,
        collate_fn=convert_to_features
    )
    valid_set = RestaurantDataset(mode='valid')
    valid_loader = DataLoader(
        valid_set,
        batch_size=cfg.batch_size,
        collate_fn=convert_to_features
    )
    # 实验题05-02：注意力、编码器、解码器、主模型
    # 初始化注意力机制
    # 注意力机制用于让解码器在生成每个词时，关注编码器输出的不同部分
    # 参数说明：
    #   enc_hid_dim: 编码器隐藏层维度，用于计算注意力分数
    #   dec_hid_dim: 解码器隐藏层维度，用于计算注意力分数

    attention = Attention(
        enc_hid_dim=cfg.enc_hid_dim,
        dec_hid_dim=cfg.dec_hid_dim
    )
    # 编码器负责将输入序列（表格数据）编码为上下文向量
    # 参数说明：
    #   input_dim: 输入词汇表大小，决定词嵌入矩阵的行数
    #   emb_dim: 词嵌入维度，将one-hot向量映射为密集向量
    #   enc_hid_dim: 编码器RNN的隐藏层维度
    #   dec_hid_dim: 解码器隐藏层维度（用于初始化解码器隐藏状态）
    #   dropout: Dropout比率，防止过拟合
    encoder = Encoder(  # 编码器类名
        input_dim=cfg.input_dim,  # 输入词汇表大小
        emb_dim=cfg.enc_emb_dim,  # 词嵌入维度
        enc_hid_dim=cfg.enc_hid_dim,
        dec_hid_dim=cfg.dec_hid_dim,
        dropout=cfg.enc_dropout  # 编码器Dropout比率
    )
    decoder = Decoder(
        output_dim=cfg.output_dim,
        emb_dim=cfg.dec_emb_dim,
        enc_hid_dim=cfg.enc_hid_dim,
        dec_hid_dim=cfg.dec_hid_dim,
        dropout=cfg.dec_dropout,
        attention=attention
        )
    # Seq2Seq模型将编码器和解码器组合在一起，实现端到端的序列到序列学习
    # 参数说明：
    #   encoder: 初始化好的编码器
    #   decoder: 初始化好的解码器
    #   src_pad_idx: 源语言填充token的ID，用于创建mask忽略填充位置
    #   device: 运行设备（CPU/GPU）

    model = Seq2Seq(  # Seq2Seq模型类名
        encoder=encoder,
        decoder=decoder,  # 传入解码器
        src_pad_idx=cfg.pad_token_id,  # 填充token ID
        device=cfg.device
    ).to(device)


    # define optimizer & criterion
    optimizer = optim.Adam(model.parameters(), lr=cfg.learning_rate)
    criterion = nn.CrossEntropyLoss(ignore_index=cfg.pad_token_id, label_smoothing=0.1)

    # train process
    best_valid_loss = float('inf')
    best_train_loss = float('inf')
    # 在 main() 函数里的训练循环
    for epoch in range(cfg.epochs):
        # 1. 计算当前的 TF 比率（从 0.7 逐渐降到 0.2）
        current_ratio = max(0.2, 0.7 - (epoch * 0.02))

        start_time = time.time()

        # 2. 调用 train 时记得传入 current_ratio
        train_loss = train(model, train_loader, optimizer, criterion, current_ratio)

        # 3. 验证不需要 ratio，保持原样
        valid_loss = evaluate(model, valid_loader, criterion)

        end_time = time.time()
        # 4. 确保这里计算了时间变量，防止报错
        epoch_mins, epoch_secs = epoch_time(start_time, end_time)

        if valid_loss < best_valid_loss:
            best_valid_loss = valid_loss
            torch.save(model.state_dict(), f'./checkpoint/best_valid_checkpoint.pt')

        # 打印报告时带上 Ratio，方便观察
        print(f'Epoch: {epoch + 1:02} | Time: {epoch_mins}m {epoch_secs}s | TF Ratio: {current_ratio:.2f}')
        print(f'\tTrain Loss: {train_loss:.3f} | Train PPL: {math.exp(train_loss):7.3f}')
        print(f'\t Val. Loss: {valid_loss:.3f} |  Val. PPL: {math.exp(valid_loss):7.3f}')
    # for epoch in range(cfg.epochs):
    #     # 1.train
    #     start_time = time.time()
    #     train_loss = train(model, train_loader, optimizer, criterion)
    #
    #     # 2.validate
    #     valid_loss = evaluate(model, valid_loader, criterion)
    #     end_time = time.time()
    #
    #     # 3.calculate the time
    #     epoch_mins, epoch_secs = epoch_time(start_time, end_time)
    #
    #     # 4.save best checkpoint (metric: valid_loss)
    #     if valid_loss < best_valid_loss:
    #         best_valid_loss = valid_loss
    #         torch.save(model.state_dict(), f'./checkpoint/best_valid_checkpoint.pt')

        if train_loss < best_train_loss:
            best_train_loss = train_loss
            torch.save(model.state_dict(), f'./checkpoint/best_train_checkpoint.pt')

        # # 5.report
        # print(f'Epoch: {epoch+1:02} | Time: {epoch_mins}m {epoch_secs}s')
        # print(f'\tTrain Loss: {train_loss:.3f} | Train PPL: {math.exp(train_loss):7.3f}')
        # print(f'\t Val. Loss: {valid_loss:.3f} |  Val. PPL: {math.exp(valid_loss):7.3f}')

    print('-------------------------------')
    print(f'Best valid loss:{best_valid_loss:.3f}')
    print(f'Best train loss:{best_train_loss:.3f}')
    print('-------------------------------')


def transfer_to_sentence(t):#将模型输出的ID列表，转换成自然语言句子
    tokens = []# 用来存储转换后的词汇
    for idx in t:
        if idx == cfg.sos_token_id or idx == cfg.pad_token_id or idx == cfg.unk_token_id:
            continue#<sos><pad><unk>跳过
        elif idx == cfg.eos_token_id:
            break#<eos>停止
        else:
            token = trg_vocab_reverse[idx]# 根据 ID 获取词汇表中的单词
            tokens.append(token)#将单词加入到 tokens 列表

    sentence = ' '.join(tokens)## 将 tokens 列表中的单词用空格连接成一个句子
    return sentence


def predict():#测试
    # access to data访问测试数据
    test_set = RestaurantDataset(mode='test')
    test_loader = DataLoader(
        test_set,
        batch_size=cfg.batch_size,
        collate_fn=convert_to_features
    )

    # model initialization初始化模型
    attention = Attention(cfg.enc_hid_dim, cfg.dec_hid_dim)
    encoder = Encoder(cfg.input_dim, cfg.enc_emb_dim, cfg.enc_hid_dim, cfg.dec_hid_dim, cfg.enc_dropout)
    decoder = Decoder(cfg.output_dim, cfg.dec_emb_dim, cfg.enc_hid_dim, cfg.dec_hid_dim, cfg.dec_dropout, attention)
    model = Seq2Seq(encoder, decoder, cfg.pad_token_id, cfg.device).to(device)

    # load checkpoint & predict加载最佳训练模型
    model.load_state_dict(torch.load('checkpoint/best_valid_checkpoint.pt'))
    model.eval()

    predict_reference = []#保存预测答案

    with torch.no_grad():# 评估时不计算梯度
        for i, batch in enumerate(test_loader):
            # src = [src_seq_len, bsz], src_len = [bsz]
            src = batch['input_ids'].to(cfg.device)# 输入序列（表格数据）
            src_len = batch['input_len'].to(cfg.device)# 输入序列长度

            # encoder_outputs = [src_len, bsz, enc_hid_dim * 2]
            # hidden = [bsz, dec_hid_dim]
            # 编码器输出
            encoder_outputs, hidden = model.encoder(src, src_len)

            # mask = [bsz, src_len]
            # 创建 mask
            mask = model.create_mask(src)

            # first input to the decoder is the <sos> tokens
            # 第一个输入给解码器的 tokens 是 <sos>（开始标记）
            bsz = src.shape[1]
            input = torch.zeros(bsz).int().to(cfg.device)
            input[:] = cfg.sos_token_id

            # tensor to store decoder outputs
            # 存储解码器的预测
            predictions = torch.zeros(cfg.max_target_len, bsz).to(cfg.device)
            # outputs = torch.zeros(cfg.max_target_len, cfg.batch_size, cfg.output_dim).to(cfg.device)
            # --- 优化后的解码循环 ---
            for t in range(cfg.max_target_len):
                output, hidden, _ = model.decoder(input, hidden, encoder_outputs, mask)

                if t > 0:
                    for b in range(bsz):
                        # 获取该 batch 之前生成过的所有词
                        prev_tokens = predictions[:t, b].unique()
                        # 降低这些词在当前步的概率（通过减去一个偏移量）
                        output[b, prev_tokens.long()] -= 1.5

                top1 = output.argmax(1)
                predictions[t] = top1
                input = top1
            # decoding解码
            # for t in range(cfg.max_target_len):
            #     output, hidden, _ = model.decoder(input, hidden, encoder_outputs, mask)
            #     top1 = output.argmax(1)# 获取最大预测值
            #     predictions[t] = top1# 将预测结果保存在 predictions 中
            #     input = top1# 将预测结果作为下一个时间步的输入

            predictions = predictions.transpose(1, 0).contiguous()#将预测结果转换为（[max_target_len, batch_size]）形状
            pred_batch = [transfer_to_sentence(t.tolist()) for t in predictions]#将每个预测结果的 token ID 转换为句子
            predict_reference.extend(pred_batch)# 添加到预测结果列表

    # save
    with open('predictions.txt', 'w', encoding='utf-8') as f:#打开predictions.txt用于保存预测结果
        for reference in predict_reference:
            f.write(reference + '\n')#将每条预测结果写入文件


if __name__ == "__main__":
    # parser通过 argparse 解析命令行输入的参数，--mode 用来指定程序的运行模式，默认为 'train'。
    parser = argparse.ArgumentParser()
    parser.add_argument('--mode', type=str, default='train')
    args = parser.parse_args()

    # get the vocabulary全局变量
    global src_vocab#词汇表加载
    global trg_vocab#存储目标词汇表
    global trg_vocab_reverse#存储目标词汇表的反向映射，索引->词汇

    src_vocab = dict()#加载源语言词汇表，将每个单词映射到其索引
    with open('vocab/source_vocab.tsv', 'r', encoding='utf-8') as f1:
        for line in f1:
            index, token = line.split('\t')
            token = token.strip('\n')
            src_vocab[token] = int(index)

    trg_vocab = dict()
    trg_vocab_reverse = dict()#读取目标词汇表
    with open('vocab/target_vocab.tsv', 'r', encoding='utf-8') as f2:
        for line in f2:
            index, token = line.split('\t')
            token = token.strip('\n')
            trg_vocab[token] = int(index)#词汇表，将目标词汇及其索引存入 trg_vocab 字典
            trg_vocab_reverse[int(index)] = token#反向词汇表，反向存储，把索引映射回词汇。

    # define arguments
    global cfg
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    # 调整参数设置，更改轮次（比如5、10）、学习率（比如1e-3 (0.001), 5e-4 (0.0005)）、batch_size（比如64,128）等参数，使得验证损失（Val.loss）低于5.1，困惑度（Val.PPL）低于170。
    # 5轮用时约20分钟左右，请注意时间安排
    # 实验题05-03：填写所有参数名称(填写前记得把要填写的内容前加注释符号)，配置所有超参数
    cfg = Config(
        device=device,
        batch_size=128,         # 批次大小 / 单次训练的样本数量
        epochs=10,              # 训练轮数 (建议调到10左右以充分训练)
        learning_rate=1e-3,     # 学习率 (设为0.001可以加速收敛)
        max_source_len=40,      # 源序列最大长度
        max_target_len=80,      # 目标序列最大长度
        input_dim=len(src_vocab),# 输入维度 (源语言词汇表大小)
        output_dim=len(trg_vocab),# 输出维度 (目标语言词汇表大小)
        enc_emb_dim=128,        # 编码器词嵌入维度
        dec_emb_dim=128,        # 解码器词嵌入维度
        enc_hid_dim=128,        # 编码器隐藏层维度
        dec_hid_dim=128,        # 解码器隐藏层维度
        enc_dropout=0.5,        # 编码器Dropout比率 (防止过拟合)
        dec_dropout=0.5         # 解码器Dropout比率 (防止过拟合)
    )
    # train/infer
    if args.mode == 'train':
        main()
    else:
        predict()
