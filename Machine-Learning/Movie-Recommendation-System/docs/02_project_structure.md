# 项目结构（第2部分）

```text
.
├── configs/
│   └── experiment.toml         # 实验参数唯一来源
├── data/
│   ├── raw/                    # 原始MovieLens 100K数据，只读
│   └── processed/              # 后续由代码生成的处理结果
├── docs/
│   ├── 01_experiment_plan.md
│   └── 02_project_structure.md
├── outputs/
│   ├── development/            # 小规模开发测试
│   └── formal/                 # 经确认后产生的正式实验结果
├── src/
│   └── movie_recommender/
│       ├── __init__.py
│       ├── config.py           # 配置读取与校验
│       ├── data.py             # 数据读取、划分、映射和负采样
│       ├── models.py           # GMF、MLP、NeuMF
│       ├── metrics.py          # HR、NDCG、AUC
│       ├── trainer.py          # 训练、验证和检查点
│       ├── evaluator.py        # 公平评估与推荐结果
│       ├── visualization.py    # 从原始CSV生成图表
│       └── reproducibility.py  # 随机种子、环境和文件哈希
├── tests/                      # 后续代码测试
├── main.py                     # 统一命令入口
└── requirements.txt
```

当前进度：

- `data.py`已实现数据读取、时间划分、负采样和数据检查；
- `models.py`已实现GMF、MLP、NeuMF及统一模型工厂；
- `trainer.py`已实现训练、验证、早停、日志和检查点；
- `metrics.py`与`evaluator.py`已实现固定候选集排序评估；
- `visualization.py`只根据原始CSV生成图表；
- `experiment.py`已实现带审计记录和防覆盖机制的正式实验流程；
- 正式训练仍被配置开关和命令确认参数双重禁止。
