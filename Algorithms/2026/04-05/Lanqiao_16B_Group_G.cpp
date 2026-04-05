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
    vector<int> w(n + 1);
    for(int i=1;i<=n;i++) cin>>w[i];
    vector<vector<int>> adj(n + 1);
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    adj[1].push_back(0);
    function<vector<bool>(int,int)> dfs = [&](int u,int fa) -> vector<bool>{
        vector<bool> f(w[u] + 1);
        if(adj[u].size() == 1)
        {
            f[0] = true;
            f[w[u]] = true;
            return f;
        }
        f[0] = true;
        for(auto &v : adj[u])
        {
            if(v == fa) continue;
            vector<bool> g = dfs(v,u);
            vector<bool> h(w[u] + 1);
            for(int i=0;i<=w[u];i++)
            {
                if(!f[i])continue;
                for(int j=0;j<g.size();j++)
                {
                    if(g[j] && i + j <= w[u])
                    {
                        h[i + j] = true;
                    }
                }
            }
            f.swap(h);
        }
        return f;
    };
    vector<bool> res = dfs(1,0);
    int ans =0;
    for(int i=0;i<=w[1];i++)
    {
        if(res[i]) ans = max(ans,i);
    }
    cout<<ans<<endl;
    return 0;
}