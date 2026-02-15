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
    int n,m;
    cin>>n>>m;
    vector<int> c(n),h(n);
    for(int i=0;i<n;i++) cin>>c[i];
    for(int i=0;i<n;i++) cin>>h[i];
    vector<vector<int>> e(n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        u --;
        v --;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    bool ok = true;
    function<void(int,int)> dfs = [&](int u,int p) {
        int sum = 0;
        for(auto v : e[u])
        {
            if(v == p) continue;
            dfs(v,u);
            c[u] += c[v];
            sum += h[v];
        }
        h[u] += c[u];
        if(h[u] % 2 != 0) ok = false;
        if (h[u] > 2 * c[u]) ok = false;
        if (h[u] < 0) ok = false; 
        if (h[u] < sum) ok = false;
    };
    dfs(0,-1);
    cout << (ok ? "YES" : "NO") << endl;
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