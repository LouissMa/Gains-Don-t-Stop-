def lowbit(n):
    return n & (-n)
n = int(input())
L = [int(x) for x in input().split()]
res = 0
for i in L:
    while i:
        i -= lowbit(i)
        res += 1
    print(res,end = " ")
    res = 0

