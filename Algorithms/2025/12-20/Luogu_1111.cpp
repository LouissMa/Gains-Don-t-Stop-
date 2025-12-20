#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
const int N = 1e5+10;
int p[N];
int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}
struct edge{
    int a,b,c;
    bool operator < (const edge &t) const{
        return c < t.c;
    }
}e[N];
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) p[i] = i;
    for(int i=1;i<=m;i++)
    {
        int x,y,t;
        cin>>x>>y>>t;
        e[i] = {x,y,t};
    }
    sort(e+1,e+1+m);
    int res = 0;
    int num = 0;
    for(int i=1;i<=m;i++)
    {
        int x = e[i].a,y = e[i].b,t = e[i].c;
        x = find(x),y = find(y);
        if(x != y)
        {
            p[y] = x;
            n--;
        }
        if(n==1)
        {
            cout<<t<<endl;
            return 0;
        }
    }
    cout<<-1<<endl;
    return 0;
}