#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e6 + 10;
int n;
int siz[N],f[N],dep[N];
vector<int> e[N];
int ans;
void dfs1(int u,int fa)
{
    siz[u] = 1;
    dep[u] = dep[fa] + 1;
    for(int v : e[u])
    {
        if(v == fa) continue;
        dfs1(v,u);
        siz[u] += siz[v];
    }
}

void dfs2(int u,int fa)
{
    for(int v : e[u])
    {
        if(v == fa) continue;
        f[v] = f[u] + n - 2 * siz[v];
        dfs2(v,u);
    }
}
signed main()
{
    SPEED;
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1,0);
    for(int i=1;i<=n;i++) f[1] += dep[i];
    dfs2(1,0);
    int id;
    for(int i=1;i<=n;i++) 
    {
        ans = max(ans,f[i]);
        if(f[i] == ans) id = i;
    }
    cout<<id<<"\n";
    return 0;
}