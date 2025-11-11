#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,q;
    cin>>n>>q;
    vector<int> f(n);
    iota(f.begin(), f.end(), 0);
    vector<array<int,10>> l(n);
    for(int i=0;i<n;i++)
    {
        l[i].fill(-1);
        l[i][0] = i+1;
    }
    auto find = [&](int x){
        while(x != f[x]) x = f[x] = f[f[x]];
        return x;
    };
    while(q--)
    {
        int op;
        cin>>op;
        if(op == 1)
        {
            int u,v;
            cin>>u>>v;
            u--;
            v--;
            u = find(u);
            v = find(v);
            if(u == v)
            {
                continue;
            }
            array<int,10> x;
            int i=0,j=0;
            while(i+j < 10)
            {
                if(l[u][i] > l[v][j])
                {
                    x[i+j] = l[u][i];
                    i++;
                }
                else
                {
                    x[i+j] = l[v][j];
                    j++;
                }
            }
            f[v] = u;
            l[u] = x;
        }
        else
        {
            int v,k;
            cin>>v>>k;
            v--;
            v = find(v);
            k--;
            cout<<l[v][k]<<"\n";
        }
    }
}