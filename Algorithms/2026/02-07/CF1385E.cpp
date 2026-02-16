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
    vector<vector<int>> e(n);
    vector<int> deg(n),pos(n);
    vector<pii> edges;
    for(int i=0;i<m;i++)
    {
        int x,u,v;
        cin>>x>>u>>v;
        u --;
        v --;
        edges.emplace_back(u,v);
        if(x == 1)
        {
            e[u].push_back(v);
            deg[v] ++;
        }
    }
    queue<int> q;
    for(int i=0;i<n;i++)
    {
        if(deg[i] == 0) q.push(i);
    }
    int cnt = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        pos[u] = cnt++;
        for(auto v : e[u])
        {
            if(--deg[v] == 0) q.push(v);
        }
    }
    if(cnt != n)
    {
        cout<<"NO\n";
        return;
    }
    else
    {
        cout<<"YES\n";
        for(auto [u,v] : edges)
        {
            if(pos[u] > pos[v]) swap(u,v);
            cout<<u+1<<" "<<v+1<<"\n";
        }
    }
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