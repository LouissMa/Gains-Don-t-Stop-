#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,a,b;
    cin>>n>>a>>b;
    a--;
    b--;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dep(n), parent(n, -1), siz(n);
    auto dfs = [&](const auto &self, int x) -> void {
        siz[x] = 1;
        for(auto y : adj[x])
        {
            if(y == parent[x]) continue;
            parent[y] = x;
            dep[y] = dep[x] + 1;
            self(self, y);
            siz[x] += siz[y];
        }
    };
    dfs(dfs, a);
    int v = (dep[b] - 1) / 2;
    while(v --)
    {
        b = parent[b];
    }
    if(siz[b] > n - siz[b])
    {
        cout<<"Bob\n";
    }
    else
    {
        cout<<"Alice\n";
    }
    return 0;
}