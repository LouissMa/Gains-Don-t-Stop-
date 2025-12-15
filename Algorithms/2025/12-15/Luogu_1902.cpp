#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int MaxN = 1010;
const int inf = 0x3f3f3f3f;
const int dx[5] = {0, 1, 0, -1, 0};
const int dy[5] = {0, 0, 1, 0, -1};
int p[MaxN][MaxN];
bool vis[MaxN][MaxN];
int n, m;
int l = 0, r = 0, mid, ans;

bool bfs(int mid)
{
    queue<PII> q;
    q.push({1,1});
    vis[1][1] = 1;
    while(q.size())
    {
        int xx = q.front().first;
        int yy = q.front().second;
        q.pop();
        if(xx == n) return true;
        for(int i=1;i<=4;i++)
        {
            int nx = xx + dx[i];
            int ny = yy + dy[i];
            if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if(vis[nx][ny] || p[nx][ny] > mid) continue;
            q.push({nx, ny});
            vis[nx][ny] = 1;
        }
    }
    return 0;
}
signed main()
{
    SPEED;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>p[i][j];
            r = max(r, p[i][j]);
        }
    }
    while(l <= r)
    {
        mid = (l + r) / 2;
        memset(vis, 0, sizeof(vis));
        if(bfs(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout<<ans<<endl;
    return 0;
}