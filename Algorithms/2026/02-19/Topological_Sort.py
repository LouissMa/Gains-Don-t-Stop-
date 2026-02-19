N = 100010

q = [0] * N
h = [-1] * N
e = [0] * N
ne = [0] * N
idx = 0
d = [0] * N #  记录入点，初始为0


def add(a, b):
    global idx
    e[idx] = b
    ne[idx] = h[a]
    h[a] = idx
    idx += 1


def topsort():
    tt = -1
    hh = 0
    # 只要入点为0，加入队列
    for i in range(1, n + 1):
        if not d[i]:
            tt += 1
            q[tt] = i

    while hh <= tt:
        a = q[hh]
        hh += 1
        # 遍历a的出边
        i = h[a]
        while i != -1:
            b = e[i]
            # 删掉a - > b的边，即删掉a
            d[b] -= 1
            # 若b的入点为0，则加入队列
            if d[b] == 0:
                tt += 1
                q[tt] = b
            i = ne[i]
    return tt == n - 1 #  此时队列保存的的次序即拓扑排序


n, m = map(int, input().split())
for _ in range(m):
    a, b = map(int, input().split())
    add(a, b)
    d[b] += 1

if topsort():
    for i in range(n):
        print(q[i], end=' ')
else:
    print(-1)