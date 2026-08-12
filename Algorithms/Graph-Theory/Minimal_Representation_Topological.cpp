#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 30005;
vector<int> adj[N];
int d[N];
int rk[N];
int topo[N];
int cnt = 0;
bitset<N> reach[N];
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        d[v] ++;
    }
    queue<int> q;
    for(int i=1;i<=n;i++)
    {
        if(d[i] == 0) q.push(i);
    }
    while(q.size())
    {
        int u = q.front();
        q.pop();
        topo[++cnt] = u;
        rk[u] = cnt;
        for(int v : adj[u])
        {
            if(--d[v] == 0)
            {
                q.push(v);
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        sort(adj[i].begin(),adj[i].end(),[](int a,int b){
            return rk[a] < rk[b];
        });
    }
    int ans = 0;
    for(int i=n;i>=1;i--)
    {
        int u = topo[i];
        reach[u].set(u);
        for(int v : adj[u])
        {
            if(reach[u].test(v))
            {
                ans ++;
            }
            else reach[u] |= reach[v];
        }
    }
    cout<<ans<<"\n";
    return 0;
}