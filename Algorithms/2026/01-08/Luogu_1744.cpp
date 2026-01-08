#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1100;
double f[N][N];
double x[N],y[N];
signed main()
{
    SPEED;
    int n,m;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) f[i][j] = 1e18;
    }
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        int a,b;
        cin>>a>>b;
        f[a][b] = f[b][a] = sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
    }
    int s,t;
    cin>>s>>t;
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                f[i][j] = min(f[i][j],f[i][k] + f[j][k]);
            }
        }
    }
    cout<<fixed<<setprecision(2)<<f[s][t]<<endl;
    return 0;
}