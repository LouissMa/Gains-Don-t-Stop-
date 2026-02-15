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

const int N = 1e5 + 10;
int e[N * 2],ne[N * 2],h[N],idx;
int vis[N];

void add(int a,int b)
{
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}

void dfs(int u,int fa)
{
    for(int i = h[u];i != -1;i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs(v,u);
        if(!vis[u] && !vis[v])
        {
            vis[u] = v;
            vis[v] = u;
        }
    }
}
void solve() 
{
    int n;
    cin>>n;
    memset(h,-1,sizeof h);
    idx = 0;
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,1);
    int ans = 0;
    for(int i=1;i<=n;i++)
    {
        if(vis[i]) ans++;
        else
        {
            int v = e[h[i]];
            ans += 2;
            vis[i] = vis[v];
            vis[v] = i;
        }
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++) cout<<vis[i]<<" ";
    cout<<"\n";
}

signed main() 
{
    SPEED;
    int t = 1;
    while(t--) 
    {
        solve();
    }
    return 0;
}