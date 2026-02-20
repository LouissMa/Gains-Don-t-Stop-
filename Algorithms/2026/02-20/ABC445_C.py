n = int(input())  # 读取数组长度
a = list(map(int, input().split()))  # 一次性读取所有输入并转换为整数列表

# 对每个元素减去 1（根据原逻辑）
for i in range(n):
    a[i] -= 1

# 按照题目要求进行变换
for i in range(n - 1, -1, -1):
    a[i] = a[a[i]]

# 输出结果（每个元素加 1）
for i in range(n):
    print(a[i] + 1, end=' ')
