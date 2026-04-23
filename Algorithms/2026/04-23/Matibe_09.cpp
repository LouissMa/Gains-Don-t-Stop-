#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e6 + 10;
vector<int> adj[N];
int dist[N];
signed main()
{
    SPEED;
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    queue<int> q;
    for(int i=1;i<=n;i++) dist[i] = -1;
    for(int i=1;i<=k;i++)
    {
        int x;
        cin>>x;
        q.push(x);
        dist[x] = 0;
    }
    int ans = 0;
    while(q.size())
    {
        int u = q.front();
        q.pop();
        ans = max(ans,dist[u]);
        for(int v : adj[u])
        {
            if(dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(dist[i] == -1) 
        {
            cout<<-1<<"\n";
            return 0;
        }
    }
    cout<<ans<<"\n";
    return 0;
}