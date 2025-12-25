#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5+10;
int a[N+2];

struct tree{
    int l,r;
    int pre;
    int add;
}t[4 * N + 2];

void build(int p,int l,int r)
{
    t[p].l = l;
    t[p].r = r;
    if(l == r)
    {
        t[p].pre = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    t[p].pre = t[p*2].pre + t[p*2+1].pre;
}

void spreed(int p)
{
    if(t[p].add)
    {
        t[p*2].pre += t[p].add * (t[p*2].r - t[p*2].l + 1);
        t[p*2+1].pre += t[p].add * (t[p*2+1].r - t[p*2+1].l + 1);
        t[p*2].add += t[p].add;
        t[p*2+1].add += t[p].add;
        t[p].add = 0;
    }
}

void change(int p,int x,int y,int z)
{
    if(x <= t[p].l && t[p].r <= y)
    {
        t[p].pre += z * (t[p].r - t[p].l + 1);
        t[p].add += z;
        return;
    }
    spreed(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if(x <= mid)
        change(p*2,x,y,z);
    if(y > mid)
        change(p*2+1,x,y,z);
    t[p].pre = t[p*2].pre + t[p*2+1].pre;
}

int ask(int p,int x,int y)
{
    if(x <= t[p].l && t[p].r <= y) return t[p].pre;
    spreed(p);
    int mid = (t[p].l + t[p].r) >> 1;
    int ans=  0;
    if(x <= mid) ans += ask(p*2,x,y);
    if(y > mid) ans += ask(p*2+1,x,y);
    return ans;
}
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int op;
        cin>>op;
        if(op == 1)
        {
            int x,y,z;
            cin>>x>>y>>z;
            change(1,x,y,z);
        }
        else
        {
            int x,y;
            cin>>x>>y;
            cout<<ask(1,x,y)<<endl;
        }
    }
    return 0;
}