#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

vector<int> a;
vector<vector<int>> e;
int n;

void dfs1(int u,int fa)
{
    for(int v : e[u])
    {
        if(v == fa) continue;
        dfs1(v,u);
        a[u] += max(0LL,a[v]);
    }
}

void dfs2(int u,int fa)
{
    for(int v : e[u])
    {
        if(v != fa)
        {
            a[v] += max(0LL,a[u] - max(0LL,a[v]));
            dfs2(v,u);
        }
    }
}
signed main()
{
    SPEED;
    cin>>n;
    e.resize(n);
    a.resize(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        if(a[i] == 0) a[i] = -1;
    }
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        u --;
        v --;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(0,-1);
    dfs2(0,-1);
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<" \n"[i == n-1];
    }
    return 0;
}