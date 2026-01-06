#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 110;
bool vis[N][N];
int f[N][N];
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) f[i][j] = 1000;
    }
    for(int i=1;i<=m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        f[a][b] = f[b][a] = c;
    }
    int k;
    cin>>k;
    for(int i=1;i<=k;i++)
    {
        int a,b;
        cin>>a>>b;
        vis[a][b] = vis[b][a] = true;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(!vis[i][j] && f[i][j] != 1000)
            {
                f[i][j] = 0;
            }
        }
    }
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                f[i][j] = f[j][i]= min(f[i][j],f[i][k] + f[k][j]);
            }
        }
    }
    int a,b;
    cin>>a>>b;
    cout<<f[a][b]<<endl;
    return 0;
}