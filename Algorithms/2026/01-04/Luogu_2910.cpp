#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

int n,m;
int ans = 0;
int dis[110][110];
int a[10010];
signed main()
{
    SPEED;
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>a[i];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>dis[i][j];
        }
    }
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                dis[i][j] = min(dis[i][j],dis[i][k] + dis[k][j]);
            }
        }
    }
    for(int i=2;i<=m;i++)
    {
        ans += dis[a[i-1]][a[i]];
    }
    cout<<ans<<endl;
    return 0;
}