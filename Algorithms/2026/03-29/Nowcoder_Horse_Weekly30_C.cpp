#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int inf = 1e18;
struct Edge {
    int v, w;
};
signed main()
{
    SPEED;
    int n,m,x;
    cin>>n>>m>>x;
    vector<int> c(n + 1, inf);
    for (int i = 2; i <= n - 1; ++i) 
    {
        cin >> c[i];
    }
    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++i) 
    {
        int u, v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    auto dijkstra = [&](int s, int op) {
        vector<int> dist(n + 1, inf);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<long long, int>>> pq;

        dist[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) 
        {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;

            for (auto [v, w] : adj[u]) 
            {
                int cost = (op == 1) ? (w - x) : ((w + 1) / 2);
                if (dist[u] + cost < dist[v]) {
                    dist[v] = dist[u] + cost;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    };
    vector<long long> d1 = dijkstra(1, 1);
    vector<long long> d2 = dijkstra(1, 2);
    vector<long long> r1 = dijkstra(n, 1);
    vector<long long> r2 = dijkstra(n, 2);
    int ans = min(d1[n], d2[n]);
    for (int i = 2; i <= n - 1; ++i) 
    {
        if (d1[i] != inf && r2[i] != inf && c[i] != inf) 
        {
            ans = min(ans, d1[i] + c[i] + r2[i]);
        }
        if (d2[i] != inf && r1[i] != inf && c[i] != inf) 
        {
            ans = min(ans, d2[i] + c[i] + r1[i]);
        }
    }

    cout << ans << "\n";

    return 0;
}