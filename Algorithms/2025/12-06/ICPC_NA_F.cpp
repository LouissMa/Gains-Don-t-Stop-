#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

struct DSU
{
    vector<int> f,siz;
    DSU(){ }
    DSU(int n)
    {
        f.resize(n);
        iota(f.begin(),f.end(),0);
        siz.assign(n,1);
    }
    int find(int x)
    {
        if(f[x] == x) return x;
        return f[x] = find(f[x]);
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
    bool merge(int x,int y)
    {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(siz[x] < siz[y]) swap(x,y);
        f[y] = x;
        siz[x] += siz[y];
        return true;
    }
    int size(int x)
    {
        return siz[x];
    }
};
signed main()
{
    SPEED;
    int n,q;
    cin>>n>>q;
    DSU dsu(n);
    vector<vector<int>> g(n);
    vector<int> a(n,0);
    int cnt = 0;
    priority_queue<int,vector<int>,greater<int>> p;
    while(q--)
    {
        char op;
        cin>>op;
        if(op == 'F')
        {
            int u,v;
            cin>>u>>v;
            u--;
            v--;
            int d = a[u];
            a[u] += a[v];
            a[v] += d;
        }
        else if(op == 'A')
        {
            int u;
            cin>>u;
            u --;
            cnt ++;
            a[u] ++;
            dsu.siz[u] ++;
        }
        else
        {
            int u;
            cin>>u;
            u--;
            
        }
    }
    return 0;
}