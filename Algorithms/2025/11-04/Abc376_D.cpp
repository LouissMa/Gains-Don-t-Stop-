#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        u--;
        v--;
        adj[u].push_back(v);
    }
    vector<int> dist(n,-1);
    queue<int> q;
    dist[0] = 0;
    q.push(0);
    int ans = m+1;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(auto y : adj[x]){
            if(y == 0)
            {
                ans = min(ans,dist[x] + 1);
            }
            if(dist[y] == -1)
            {
                dist[y] = dist[x] + 1;
                q.push(y);
            }
        }
    }
    if(ans == m+1) ans = -1;
    cout<<ans<<endl;
    return 0;
}