# 附录A 实验真实性与结果来源说明

为保证实验数据真实、结果可核验，本文保留了从原始数据到论文图表的完整实验记录。实验使用GroupLens公开发布的MovieLens 100K数据集，原始评分文件未进行人工修改。程序在正式训练开始时记录数据文件和源代码的SHA-256哈希，并保存Python、PyTorch、CUDA及GPU环境信息。

三种模型的每轮训练损失和验证指标均由训练程序自动写入`training_history.csv`，测试指标由最优模型检查点在固定测试候选集上计算后自动写入`test_metrics.csv`。个性化推荐案例由保存的NeuMF模型对用户全部未评分电影进行前向计算并排序，原始结果保存在`user_1_neumf_top10.csv`。论文中的实验表格仅对CSV中的原始数值进行小数位格式化，没有人工补写或修改指标。

表4-3中的“实际训练轮数、最佳轮次和最佳验证NDCG@10”来自逐轮训练日志，而不是`test_metrics.csv`。三种模型的原始记录如下：

| 模型 | 实际训练轮数 | 最佳轮次 | 最佳验证NDCG@10 |
|---|---:|---:|---:|
| GMF | 8 | 3 | 0.24812441617519868 |
| MLP | 30 | 30 | 0.4356342715815523 |
| NeuMF | 30 | 29 | 0.4496886803012786 |

其中，GMF虽然实际运行到第8轮，但第3轮的验证NDCG@10最高，因此最佳轮次是3而不是8。第8轮是触发早停时的最后训练轮次。上述最佳轮次和指标同时保存在`gmf_best.pt`、`mlp_best.pt`和`neumf_best.pt`检查点元数据中。

## 附图A-1 正式实验训练记录与测试结果

截图建议同时显示以下内容：

1. `outputs/formal/training_history.csv`中的模型名称、训练轮次、训练损失和验证指标；
2. `outputs/formal/test_metrics.csv`中的GMF、MLP和NeuMF测试指标；
3. 编辑器左侧文件列表中的`models`、`figures`、`environment.json`和`file_hashes.json`。

截图时可在`training_history.csv`中筛选或定位以下三行：

- GMF第3轮：`validation_ndcg@10 = 0.24812441617519868`；
- MLP第30轮：`validation_ndcg@10 = 0.4356342715815523`；
- NeuMF第29轮：`validation_ndcg@10 = 0.4496886803012786`。

图题：

> 图A-1 正式实验训练日志、模型文件与测试指标原始记录

正文说明：

> 如图A-1所示，正式实验目录同时保存了逐轮训练日志、最优模型检查点、测试指标、运行环境及文件哈希。论文表4-3和表4-4中的数据分别来源于训练日志和测试指标CSV。

## 附图A-2 模型加载与个性化推荐运行结果

在项目根目录的PowerShell终端运行：

```powershell
python main.py recommend --model neumf --user-id 1 --top-k 10
```

截图必须保留终端中的完整命令，并显示输出的用户编号、推荐排名、电影名称、类型和模型分数。不要只截取结果区域，否则无法证明结果由该命令产生。

图题：

> 图A-2 加载正式NeuMF模型生成用户1的Top-10电影推荐

正文说明：

> 如图A-2所示，程序加载正式训练保存的NeuMF最优模型，排除用户1已经评分的电影，对其余候选电影计算匹配分数，并输出Top-10推荐结果。终端结果与`user_1_neumf_top10.csv`中的原始记录一致。

## 可核验文件

| 证据内容 | 文件 |
|---|---|
| 原始评分数据 | `data/raw/ml-100k/u.data` |
| 正式实验配置 | `outputs/formal/experiment_config.toml` |
| 环境信息 | `outputs/formal/environment.json` |
| 数据与源码哈希 | `outputs/formal/file_hashes.json` |
| 每轮训练记录 | `outputs/formal/training_history.csv` |
| 测试指标 | `outputs/formal/test_metrics.csv` |
| NeuMF最优模型 | `outputs/formal/models/neumf/neumf_best.pt` |
| 推荐案例 | `outputs/formal/user_1_neumf_top10.csv` |

附录截图用于辅助证明实验过程，最终真实性仍由原始数据、源代码、模型检查点和未经修改的结果文件共同支持。
