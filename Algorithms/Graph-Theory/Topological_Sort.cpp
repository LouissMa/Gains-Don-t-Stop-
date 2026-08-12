#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5 + 10;
int h[N],e[N],ne[N],idx;
int n,m;
int q[N],d[N];

void add(int a,int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

bool topsort()
{
    int hh = 0,tt = -1;
    for(int i=1;i<=n;i++)
    {
        if(!d[i]) q[++tt] = i;
    }
    while(hh <= tt)
    {
        int t = q[hh ++];
        for(int i=h[t];~i;i = ne[i])
        {
            int j = e[i];
            d[j] --;
            if(d[j] == 0) q[++tt] = j;
        }
    }
    return tt == n - 1;
}
signed main()
{
    SPEED;
    cin>> n >> m;
    memset(h,-1,sizeof h);
    idx = 0;
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        add(u,v);
        d[v] ++;
    }
    if(!topsort()) cout<<-1<<"\n";
    else 
    {
        for(int i=0;i<n;i++) cout<<q[i]<<" \n"[i == n - 1];
    }
    return 0;
}