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

void solve() 
{
    int n,S;
    cin>>n>>S;
    vector<vector<pii>> e(n);
    for(int i=1;i<n;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        u --;
        v --;
        e[u].push_back({v,w});
        e[v].push_back({u,w});
    }
    vector<int> siz(n),weight(n);
    function<void(int, int)> dfs = [&](int u, int p) {
        if(p != -1 && e[u].size() == 1)
        {
            siz[u] = 1;
        }
        for(auto [v,w] : e[u])
        {
            if(v == p) continue;
            weight[v] = w;
            dfs(v,u);
            siz[u] += siz[v];
        }
    };
    dfs(0,-1);
    for(int i=0;i<n;i++)
    {
        S -= 1LL * siz[i] *weight[i];
    }
    priority_queue<pii> h;
    for(int i=0;i<n;i++)
    {
        h.emplace(1LL * siz[i] * ((weight[i] + 1)/2),i);
    }
    int ans = 0;
    while(S < 0)
    {
        auto [w,u] = h.top();
        h.pop();
        ++ans;
        S += w;
        weight[u] /= 2;
        h.emplace(1LL * siz[u] *((weight[u] + 1) / 2),u);
    }
    cout<<ans<<"\n";
}

signed main() 
{
    SPEED;
    int t = 1;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}