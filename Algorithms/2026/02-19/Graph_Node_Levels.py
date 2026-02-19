import collections

def bfs():
    d = [-1] * (n + 1)
    d[1] = 0
    queue = collections.deque([1])
    while queue:
        u = queue.popleft()
        if u in g:
            for v in g[u]:
                if d[v] == -1:
                    d[v] = d[u] + 1
                    queue.append(v)
    return d[n]


n,m = map(int,input().split())
g = collections.defaultdict(list)
for i in range(m):
    a,b = map(int,input().split())
    g[a].append(b)
print(bfs())