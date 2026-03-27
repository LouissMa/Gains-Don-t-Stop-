/*
Problem: Problem Title
Contest: Contest Name
URL: URL
Memory Limit: 1024 MB
Time Limit: 2000 ms

Description:
Paste problem statement here
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;
#define inf 0x3f3f3f3f
#define maxn 5010
typedef double db;
int n, m;
int a[maxn], b[maxn], c[maxn], d[maxn], e[maxn];
db p[maxn];
db f[maxn][maxn][4];
void solve() 
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i]>>c[i]>>d[i]>>e[i]>>p[i],p[i]/=100;
    for(int j=0;j<=m;j++)
    {
        for(int k=0;k<=3;k++)
        {
            f[n+1][j][k] = 0;
        }
    }
    for(int i=n;i>=1;i--)
    {
        for(int j=0;j<=m;j++)
        {
            for(int k=0;k<=3;k++)
            {
                f[i][j][k] = 0;
                db f1 = -1e200;
                if(j >= b[i])
                {
                    f1 = a[i] + (p[i] * f[i + 1][j - b[i]][k | 1]) + ((1 - p[i]) * (f[i + 1][j - b[i]][k | 2]));
                }
                db f2 = -1e200;
                if(k < 3 && j >= d[i])
                {
                    f2 = c[i] + (p[i] * f[i + 1][j - d[i]][k | 1]) + (1 - p[i]) * (f[i + 1][j - d[i]][k | 2]);
                }
                if(k == 3 && j >= e[i] + d[i])
                {
                    f2 = c[i] + (f[i + 1][j - d[i] - e[i]][0]);
                }
                f[i][j][k] = max(f1, f2);
            }
        }
    }
    db res = f[1][m][0];
    if(res < 0) cout<<-1<<endl;
    else printf("%.12lf\n", res);
}

signed main() 
{
    SPEED;
    int t = 1;
    while(t--) 
    {
        solve();
    }
    return 0;
}