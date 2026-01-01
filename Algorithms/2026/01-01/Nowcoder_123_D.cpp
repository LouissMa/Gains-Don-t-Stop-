#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2e5+10;
int n,m;
int dist[N],minedge[N];
bool vis[N];
vector<PII> vec[N];

void dijkstra()
{
    for(int i=1;i<=n;i++) dist[i]=1e18;
    dist[1] = 0;
    priority_queue<PII,vector<PII>,greater<PII>> q;
    q.push({0,1});
    while(q.size())
    {
        auto [d,u] = q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(auto &v : vec[u])
        {
            int j = v.first;
            int t = v.second;
            if(dist[j] > dist[u] + t)
            {
                dist[j] = dist[u] + t,
                q.push({dist[j],j});
            }
        }
    }
}
signed main()
{
    SPEED;
    cin>>n>>m;
    for(int i=1;i<=n;i++) minedge[i]=1e18;
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        vec[u].push_back({v,w});
        vec[v].push_back({u,w});
        minedge[u] = min(minedge[u],w);
        minedge[v] = min(minedge[v],w);
    }
    for(int i=1;i<=n;i++)
    {
        for(auto &j : vec[i])
        {
            vec[i].push_back({j.first,2 * minedge[i]});
        }
    }
    dijkstra();
    if(dist[n] == 1e18) cout<<-1<<endl;
    else cout<<dist[n]<<endl;
    return 0;
}