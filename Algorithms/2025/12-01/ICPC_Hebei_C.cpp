#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin>>n;
    vector<vector<PII>> adj(n);
    for(int i=0;i<n-1;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        u--;
        v--;
        w %= 2;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    int ans = 0;
    vector<array<int,2>> dp(n,array<int,2>{0,0});
    auto dfs = [&](const auto &self, int u, int fa) -> void{
        array<int,2> c{0,0};
        for(auto [v,w] : adj[u])
        {
            if(v== fa) continue;
            self(self,v,u);
            ans += dp[v][w ^ 1];
            for(int i=0;i<2;i++)
            {
                ans += c[i] * dp[v][i^w^1];
                c[i] += dp[v][i^w];
                dp[u][i] += dp[v][i^w];
            }
        }
        dp[u][0] += 1;
    };
    dfs(dfs,0,-1);
    cout<<ans<<endl;
    return 0;
}