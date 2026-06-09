# 基于神经协同过滤的个性化电影推荐方法研究

本项目用于完成《深度学习》期末大作业，使用MovieLens 100K数据集，对比GMF、MLP和NeuMF三种神经协同过滤模型。

当前进度：

- 第1部分：实验方案已整理；
- 第2部分：项目结构与配置入口已搭建；
- 第3部分：数据处理、时间划分和负采样代码已完成；
- 第4部分：GMF、MLP和NeuMF模型代码已完成；
- 第5部分：训练、早停、检查点和日志代码已完成；
- 第6部分：指标、评估、推荐案例和可视化代码已完成；
- 第7部分：人工小数据完整测试已完成；
- 第8部分：正式实验参数已确认并写入配置；
- 数据集已由MovieLens 1M切换为更轻量的MovieLens 100K，旧1M数据和不完整训练结果已清理；
- 第9部分：MovieLens 100K三模型最终30轮训练已经完成；
- 当前重新关闭训练许可，防止覆盖正式结果。

详细方案见：

- `docs/01_experiment_plan.md`
- `docs/02_project_structure.md`
- `docs/03_formal_parameters.md`
- `docs/04_formal_results.md`

检查当前配置：

```powershell
python main.py
```

该命令只读取并展示配置，不处理数据、不创建实验指标，也不训练模型。

旧原型和旧训练输出已经清理，不得恢复为正式论文实验结果。

运行第3、4部分单元测试：

```powershell
python -m unittest discover -s tests -v
```

测试只使用人工构造的小数据和张量，不会执行正式训练。

正式训练受到双重保护：

1. `configs/experiment.toml`中的`formal_training_approved`必须为`true`；
2. 命令必须显式包含`--confirm-formal-training`。

在共同确认参数前，不应修改训练许可开关。

训练完成后可直接展示个性化推荐：

```powershell
python main.py recommend --model neumf --user-id 1 --top-k 10
```

该命令排除用户已经评分的电影，对其余电影逐一打分，并输出带电影名称、类型和模型分数的Top-10推荐列表。
