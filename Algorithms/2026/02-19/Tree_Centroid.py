N = 100010
#将重心删除后，各个连通块中点数的最大值，即本题的答案。先初始化为最大值
ans = N

def add(a, b):
    global idx

    e[idx] = b
    ne[idx] = h[a]
    h[a] = idx 
    idx += 1

# 深度优先遍历一般都有个for循环，
# 然后再在for循环中深度遍历

def dfs(u):     #返回的是包含u节点的所有子节点个数
    global ans

    #标记已访问的树节点
    st[u] = True

    sum = 1     #以u为根节点的节点数，即dfs要返回的值
    res = 0     #删除节点u后，最大连通子图的节点数
    #遍历子节点

    i = h[u]    #找到存储u节点子节点的idx
    while i != -1:
        j = e[i]
        if not st[j]:
            #向下递归，找到以j为根的树的大小
            s = dfs(j)
            #求最大连通子图的大小
            res = max(res, s)
            sum += s
        i = ne[i]

    #在把u的所有子节点都遍历一遍之后，可以得到u的根节点对应的连通块的个数,
    res = max(res, n-sum)
    #上面算出的res就是删除u之后的对应最大连通块个数，然后放到最后答案里比较找最小值
    ans = min(ans, res)
    return sum  #别忘了dfs返回的是u的子树个数+1


#//以有向图的格式存储无向图，所以每个节点至多对应2n-2条边
h, e, ne, idx = [-1]*N, [0]*2*N, [0]*2*N, 0
st = [False]*N
n = int(input())

for i in range(n-1):
    a, b = map(int, input().split())    ## 无向图，所以要从a->b,b->a都要插入一条边
    add(a, b)
    add(b, a)       #//无向图

dfs(1)
print(ans)