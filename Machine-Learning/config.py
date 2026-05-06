class Config():
    def __init__(
            self,
            device=None,
            batch_size=64,
            epochs=10,
            learning_rate=1e-4,
            max_source_len=40,#table输入最大长度超过的会被截断
            max_target_len=80,
            pad_token_id=0,#<pad> 的编号是 0，用来补齐 batch 里长度不同的序列
            unk_token_id=1,#<unk>：词表里没有的词，防止模型直接报错
            sos_token_id=2,#<sos>：start of sentence，decoder 第一个输入
            eos_token_id=3,
            input_dim=0,#实际值 = len(source_vocab)
            output_dim=0,#决定 decoder 输出层维度
            enc_emb_dim=256,#encoder embedding向量维度
            dec_emb_dim=256,#同上，但用于 decoder
            enc_hid_dim=512,#encoder GRU 的 hidden size
            dec_hid_dim=512,#decoder GRU 的 hidden size
            enc_dropout=0.1,#encoder embedding 后 dropout防止过拟合
            dec_dropout=0.1#decoder embedding 后 dropout
    ):

        # training setting & hyper parameters
        self.device = device
        self.batch_size = batch_size
        self.epochs = epochs
        self.learning_rate = learning_rate
        self.max_source_len = max_source_len
        self.max_target_len = max_target_len
        # special tokens
        self.pad_token_id = pad_token_id
        self.unk_token_id = unk_token_id
        self.sos_token_id = sos_token_id
        self.eos_token_id = eos_token_id
        # model parameters
        self.input_dim = input_dim
        self.output_dim = output_dim
        self.enc_emb_dim = enc_emb_dim
        self.dec_emb_dim = dec_emb_dim
        self.enc_hid_dim = enc_hid_dim
        self.dec_hid_dim = dec_hid_dim
        self.enc_dropout = enc_dropout
        self.dec_dropout = dec_dropout
