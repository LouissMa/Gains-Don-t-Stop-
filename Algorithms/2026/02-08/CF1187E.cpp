#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2e5 + 10;
int n;
int e[2 * N],ne[N * 2],h[N],idx;
void add(int a,int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
int siz[N];
int dp[N];

void dfs1(int u,int fa)
{
    siz[u]=1;
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if(j==fa)continue;
        dfs1(j,u);
        siz[u]+=siz[j];
    }
    dp[1]+=siz[u];
}

void dfs2(int u,int fa)
{
    for(int i=h[u];~i;i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        dp[j] = dp[u] + n - 2 * siz[j];
        dfs2(j,u);
    }
}
signed main()
{
    SPEED;
    cin>>n;
    memset(h,-1,sizeof h);
    idx = 0;
    for(int i=1;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        add(a,b);
        add(b,a);
    }
    dfs1(1,1);
    dfs2(1,1);
    int ans = 0;
    for(int i=1;i<=n;i++)
    {
        ans = max(ans,dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}