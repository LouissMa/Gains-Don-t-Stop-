# 个性化推荐功能说明

本项目的核心是深度学习推荐算法，不是普通电影管理系统。推荐功能通过以下流程体现：

1. 读取指定用户的历史评分；
2. 排除该用户已经评分的电影；
3. 使用训练完成的GMF、MLP或NeuMF模型，对所有剩余电影计算偏好分数；
4. 按模型分数从高到低排序；
5. 输出Top-N电影的名称、类型和分数。

命令示例：

```powershell
python main.py recommend --model neumf --user-id 1 --top-k 10
```

保存推荐结果：

```powershell
python main.py recommend --model neumf --user-id 1 --top-k 10 --save-csv outputs/formal/user_1_top10.csv
```

模型对比用于证明候选推荐算法的有效性，Top-N输出用于展示算法如何完成实际个性化电影推荐。两者共同构成“推荐方法研究与演示”，方向与题目一致。
