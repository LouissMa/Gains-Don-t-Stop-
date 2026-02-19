N = 1010
a = [[0] * N for _ in range(N)]
s = [[0] * N for _ in range(N)]

n,m,q = map(int,input().split())
for i in range(1,n + 1):
    a[i] = [0] + list(map(int,input().split())) + a[m + 1:]
for i in range(1,n + 1):
    for j in range(1 , m + 1):
        s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j]
while q:
    x1,y1,x2,y2 = map(int,input().split())
    print(s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1-1][y1 - 1])
    q -= 1