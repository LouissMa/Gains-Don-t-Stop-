#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m,k;
    cin>>n>>m>>k;
    vector<vector<PII>> g(n);
    while(m --)
    {
        int u,v,w;
        cin>>u>>v>>w;
        u--;v--;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    auto dijkstra = [&](int s)
    {
        vector<int> dist(n,1e18);
        priority_queue<PII,vector<PII>,greater<PII>> q;
        dist[s] = 0;
        q.push({0,s});
        while(!q.empty())
        {
            auto [d,u] = q.top();
            q.pop();
            if(d > dist[u]) continue;
            for(auto [v,w] : g[u])
            {
                if(dist[v] > d + w)
                {
                    dist[v] = d + w;
                    q.push({dist[v],v});
                }
            }
        }
        return dist;
    };
    vector<int> p(k + 2);
    p[0] = 0;
    for(int i=1;i<=k;i++) cin>>p[i],p[i] --;
    p[k + 1] = n - 1;
    int ans = 0;
    for(int i=0;i<k + 1;i++)
    {
        vector<int> d = dijkstra(p[i]);
        ans += d[p[i + 1]];
    }
    cout<<ans<<endl;
    return 0;
}