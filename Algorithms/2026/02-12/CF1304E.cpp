#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
const int N = 1e5 + 10;
int h[N],e[N * 2],ne[N * 2],idx;
int p[N];
int d[N];
int f[N][20];
int n;
void add(int a,int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int u,int fa)
{
    p[u] = fa;
    d[u] =d[fa] + 1;
    for(int i=h[u];~i;i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs(v,u);
    }
}

void init()
{
    for(int i=1;i<=n;i++) f[i][0] = p[i];
    for(int i=1;i<=19;i++)
    {
        for(int j=1;j<=n;j++)
        {
            f[j][i] = f[f[j][i-1]][i-1];
        }
    }
}

int lca(int a,int b)
{
    if(d[a] < d[b]) swap(a,b);
    for(int i=19;i>=0;i--)
    {
        if(d[f[a][i]] >= d[b]) a = f[a][i];
    }
    for(int i=19;i>=0;i--)
    {
        if(f[a][i] != f[b][i])
        {
            a = f[a][i];
            b = f[b][i];
        }
    }
    if(a != b) return p[a];
    else return a;
}

int dist(int u,int v)
{
    int l = lca(u,v);
    int res = d[u] + d[v];
    res -= d[l] * 2;
    return res;
}
signed main()
{
    SPEED;
    cin>>n;
    idx = 0;
    memset(h,-1,sizeof h);
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(1,1);
    init();
    int q;
    cin>>q;
    while(q --)
    {
        int x,y,a,b,k;
        cin>>x>>y>>a>>b>>k;
        int res = dist(a,b);
        if(res <= k && res % 2 == k % 2)
        {
            cout<<"YES\n";
            continue;
        }
        res = dist(a,x) + dist(b,y) + 1;
        if(res <= k && res % 2 == k % 2)
        {
            cout<<"YES\n";
            continue;
        }
        res = dist(a,y) + dist(b,x) + 1;
        if(res <= k && res % 2 == k % 2)
        {
            cout<<"YES\n";
            continue;
        }
        cout<<"NO\n";
    }
    return 0;
}