#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5 +10;
vector<int> adj[N];
int dp[N][2];

void dfs(int u,int fa)
{
    dp[u][0] = 1;
    dp[u][1] = 0;
    int sum = 0;
    int maxx = 0;
    for(auto v : adj[u])
    {
        if(v == fa) continue;
        dfs(v,u);
        sum += dp[v][1];
        maxx = max(maxx,dp[v][0] - dp[v][1]);
    }
    dp[u][0] += sum;
    dp[u][1] += sum + maxx;
}
signed main()
{
    SPEED;
    int n;
    cin>>n;
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    cout<<max(dp[1][0],dp[1][1])<<"\n";
    return 0;
}