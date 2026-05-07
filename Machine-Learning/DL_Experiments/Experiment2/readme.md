// 深度学习课的代码示例，仅供参考...

#### 1. 示例代码结构

```
.
├── checkpoint					# 保存训练好的checkpoint的文件夹
├── config.py					# 参数配置文件
├── data						# 处理好的数据集文件夹
│   ├── testset.csv
│   ├── trainset.csv
│   └── validset.csv
├── dataloader.py				# 数据集读取文件
├── main.py						# 训练/预测文件
├── model.py					# 模型定义文件
├── raw_data					# 未处理的数据集文件夹
│   ├── testset.csv
│   ├── trainset.csv
│   └── validset.csv
└── vocab						# 数据集词典文件夹
    ├── source_vocab.tsv
    └── target_vocab.tsv
```

#### 2. 训练/预测方法

- 训练并保存模型：

```shell
python main.py --mode 'train'
```

- 使用保存好的模型预测：

```shell
python main.py --mode 'predict'
```

#### 3. 注意事项

- 代码的预测效果不太好，或许可以通过调整main.py中的cfg中的参数值得到更好的效果，也可以对网络部分进行修改（目前网络层数等方面太少了...）；
- 代码仅仅是Seq2Seq任务代码流程的参考，不保证没有bug.

