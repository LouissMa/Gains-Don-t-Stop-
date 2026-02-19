N = 100010
n = int(input())
res = [0]*N 
data = list(map(int,input().split()))
j = 0
# 用来保存最大长度结果
num = 0
for i in range(n):
    res[data[i]] += 1
    # 当序列中出现了重复的元素，就把j下标的数弹出，并且j++
    while res[data[i]] > 1:
        res[data[j]] -= 1
        j += 1
    num = max(num,i-j+1)
print(num)

"""
n = int(input())
data = list(map(int,input().split()))
# 创建字典并把所有键的值初始化为0
dic = dict.fromkeys(data,0)
num = 0
j = 0
for i in range(n):
    dic[data[i]] += 1
    # 当字典中出现了值大于1的键，就把j下标的键值弹出，并且j++
    while dic[data[i]] > 1:
        dic[data[j]] -= 1
        j += 1
    num = max(num,i-j+1)
print(num)
"""