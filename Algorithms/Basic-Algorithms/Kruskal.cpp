#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 100010,M = 200010,INF = 0x3f3f3f3f;
int n,m;
int p[N];

struct Edge
{
    int a,b,c;
    bool operator<(const Edge &t) const
    {
        return c < t.c;
    }
}edges[M];

int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}
signed main()
{
    SPEED;
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        edges[i] = {a,b,c};
    }
    sort(edges,edges+m);
    for(int i=1;i<=n;i++) p[i] = i;
    int res = 0,cnt = 0;
    for(int i=0;i<m;i++)
    {
        int a = edges[i].a,b = edges[i].b,c = edges[i].c;
        a = find(a);
        b = find(b);
        if(a != b)
        {
            p[a] =  b;
            res += c;
            cnt ++;
        }
    }
    if(cnt < n-1) cout<<"impossible"<<endl;
    else cout<<res<<endl;
    return 0;
}