#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 210;
int n,k;
int e[N*2],ne[N*2],h[N],idx;
int a[N];
int dp[N][N];
void add(int a,int b)
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

void dfs(int u,int fa)
{
    dp[u][0] = a[u];
    for(int i=h[u];i!=-1;i=ne[i])
    {
        if(e[i] == fa) continue;
        dfs(e[i],u);
    }
    for(int d = 0;d < n;d++)
    {
        if(d == 0)
        {
            for(int i = h[u];i!=-1;i=ne[i])
            {
                int v = e[i];
                if(v == fa) continue;
                dp[u][0] += dp[v][max(0LL,k-1)];
            }
        }
        else
        {
            for(int i=h[u];i != -1;i=ne[i])
            {
                int v = e[i];
                if(v == fa) continue;
                int res = dp[v][d - 1];
                for(int j = h[u];j!=-1;j=ne[j])
                {
                    int now = e[j];
                    if(now == v || now == fa) continue;
                    res += dp[now][max(d - 1,k - d - 1)];
                }
                dp[u][d] = max(dp[u][d],res);
            }
        }
    }
    for(int d=n-1;d;d--)dp[u][d-1]=max(dp[u][d-1],dp[u][d]);
}
signed main()
{
    SPEED;
    cin>>n>>k;
    k++;
    memset(h,-1,sizeof h);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        add(u,v),add(v,u);
    }
    dfs(1,1);
    cout<<dp[1][0]<<"\n";
}