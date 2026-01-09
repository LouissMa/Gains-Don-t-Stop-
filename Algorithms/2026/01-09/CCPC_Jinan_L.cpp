#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
const int N = 2e5+10;
struct BIT{
    int a[N];
    int t[N];
    void c(int x,int d)
    {
        d -= a[x];
        a[x] += d;
        for(;x < N;x+= x & -x) t[x] += d;
    }
    int q(int x)
    {
        int sum = 0;
        for(;x;x -= x & -x) sum += t[x];
        return sum;
    }
    int q(int l,int r)
    {
        return q(r) - q(l-1);
    }
}T;
int n,m;
int a[N];
int fa[N],ch[N][2];

void init()
{
    int h = 1,t = n;
    while(t - h + 1 >= 2)
    {
        fa[h] = fa[h+1] = ++t;
        ch[t][0] = h;
        ch[t][1] = h+1;
        a[t] = min(a[h],a[h+1]);
        T.c(t,max(a[h],a[h+1]));
        h += 2;
    }
}

void updt(int x)
{
    for(x = fa[x];x;x = fa[x])
    {
        a[x] = min(a[ch[x][0]],a[ch[x][1]]);
        T.c(x,max(a[ch[x][0]],a[ch[x][1]]));
    }
}

int query(int x,int y)
{
    return T.q(n + x,n + y);
}
signed main()
{
    SPEED;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    init();
    while(m--)
    {
        char op;
        cin>>op;
        int x,y;
        cin>>x>>y;
        if(op == 'C')
        {
            swap(a[x],a[y]);
            updt(x);
            updt(y);
        }
        else
        {
            cout<<query(x,y)<<endl;
        }
    }
    return 0;
}