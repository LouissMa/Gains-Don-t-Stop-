#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5 + 10;
int n;
int val[N],siz[N],dp1[N],dp2[N];

int h[N],e[2 * N],ne[2 * N],w[2 * N],idx;

void add(int a,int b,int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void dfs1(int u,int fa)
{
    siz[u] = val[u];
    for(int i=h[u];i!=-1;i=ne[i])
    {
        int j = e[i];
        int k = w[i];
        if(j == fa) continue;
        dfs1(j,u);
        siz[u] += siz[j];
        dp1[u] += dp1[j] + k * siz[j];
    }
}

void dfs2(int u,int fa)
{
    for(int i=h[u];i!=-1;i=ne[i])
    {
        int v = e[i];
        int k = w[i];
        if(v == fa) continue;
        int cost = dp2[u] + dp1[u] - (dp1[v] + k * siz[v]);
        int ex_cost = (siz[1] - siz[v]) * k;
        dp2[v] = cost + ex_cost;
        dfs2(v,u);
    }
}
signed main()
{
    SPEED;
    cin>>n;
    memset(h,-1,sizeof h);
    for(int i=1;i<=n;i++) cin>>val[i];
    for(int i=1;i<n;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    dfs1(1,0);
    dfs2(1,0);
    int ans = 1e18;
    for(int i=1;i<=n;i++) ans = min(ans,dp1[i] + dp2[i]);
    cout<<ans<<"\n";
    return 0;
}