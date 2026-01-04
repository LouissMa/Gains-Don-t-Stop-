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
    vector<vector<int>> vec(n);
    vector<int> in(n),dist(n);
    for(int i=0;i<n;i++) 
    {
        dist[i] = -1;
        in[i] = 0;
        vec[i].clear();
    }
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        cin>>u>>v;
        u--;v--;
        vec[u].push_back(v);
        vec[v].push_back(u);
        in[u]++;
        in[v]++;
    }
    queue<int> q;
    for(int i=0;i<n;i++)
    {
        if(in[i] == 1)
        {
            q.push(i);
            dist[i] = 0;
        }
    }
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for(auto v : vec[u])
        {
            if(dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    int maxx = 0;
    for(int i=0;i<n;i++)
    {
        if(in[i] != 1) maxx = max(maxx,dist[i]);
    }
    vector<int> ans;
    for(int i=0;i<n;i++)
    {
        if(dist[i] == maxx && in[i] != 1)
        {
            ans.push_back(i+1);
        }
    }
    cout<<ans.size()<<"\n";
    for(int i=0;i<ans.size();i++)
    {
        cout<<ans[i]<<" \n"[i==ans.size()-1];
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