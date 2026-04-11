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
    int n;
    cin>>n;
    vector<vector<tuple<int, int, int>>> e(n);
    int S;
    cin>>S;
    for(int i=1;i<n;i++)
    {
        int u,v,w,c;
        cin>>u>>v>>w>>c;
        u --;
        v --;
        e[u].push_back({v,w,c});
        e[v].push_back({u,w,c});
    }
    vector<int> siz(n),weight(n),cost(n);
    function<void(int,int)> dfs = [&](int u,int p){
        if(p != -1 && e[u].size() == 1) siz[u] = 1;
        for(auto [v,w,c] : e[u])
        {
            if(v == p) continue;
            weight[v] = w;
            cost[v] = c;
            dfs(v,u);
            siz[u] += siz[v];
        }
    };
    dfs(0,-1);
    for(int i=1;i<n;i++)
    {
        S -= siz[i] * weight[i];
    }
    int ans = 1e9;
    vector<vector<int>> v(2);
    for(int i=1;i<n;i++)
    {
        for( ; weight[i] > 0;weight[i] /= 2)
        {
            v[cost[i] - 1].push_back(1ll * siz[i] * ((weight[i] + 1) / 2));
        }
    }
    for(int c = 0;c<2;c++)
    {
        sort(v[c].begin(),v[c].end(),greater<int>());
    }
    int res = 0;
    for(auto x : v[0]) res += x;
    for(int i=0,j = v[0].size();i<=v[1].size();i ++)
    {
        while(j > 0 && res - v[0][j-1] + S >= 0)
        {
            -- j;
            res -= v[0][j];
        }
        if(res + S >= 0) ans = min(ans,2 * i + j);
        if(i < v[1].size()) res += v[1][i];
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