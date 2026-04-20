#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e4 +10;
int n,m;
int a[N + 2];

struct tree{
    int l,r;
    int pre;
    int add;
    int mx;
}t[N * 4 + 2];

void push_up(int p)
{
    t[p].pre = t[p * 2].pre + t[p * 2 + 1].pre;
    t[p].mx = max(t[p * 2].mx,t[p * 2 + 1].mx);
}

void build(int p,int l,int r)
{
    t[p].l = l;
    t[p].r = r;
    if(l == r)
    {
        t[p].pre = t[p].mx = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p * 2,l,mid);
    build(p * 2 + 1,mid + 1,r);
    push_up(p);
}

void speed(int p)
{
    if(t[p].add)
    {
        t[p*2].pre += t[p].add * (t[p*2].r - t[p*2].l + 1);
        t[p*2].mx += t[p].add; 
        t[p*2].add += t[p].add;
        
        t[p*2+1].pre += t[p].add * (t[p*2+1].r - t[p*2+1].l + 1);
        t[p*2+1].mx += t[p].add;
        t[p*2+1].add += t[p].add;
        
        t[p].add = 0;
    }
}

void change_add(int p,int x,int y,int z)
{
    if(x <= t[p].l && t[p].r <= y)
    {
        t[p].pre += z * (t[p].r - t[p].l + 1);
        t[p].mx += z;
        t[p].add +=z;
        return;
    }
    speed(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if(x <= mid) change_add(p * 2,x,y,z);
    if(mid < y) change_add(p * 2 + 1,x,y,z);
    push_up(p);
}

void change_min(int p,int x,int y,int z)
{
    if(t[p].mx <= z) return;
    if(t[p].l == t[p].r)
    {
        t[p].pre = z;
        t[p].mx = z;
        return;
    }
    speed(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if(x <= mid) change_min(p * 2,x,y,z);
    if(mid < y) change_min(p * 2 + 1,x,y,z);
    push_up(p);
}
int ask(int p,int x,int y)
{
    if(x <= t[p].l && t[p].r <= y) return t[p].pre;
    speed(p);
    int mid = (t[p].l + t[p].r) >> 1;
    int ans = 0;
    if(x <= mid) ans += ask(p * 2,x,y);
    if(mid < y) ans += ask(p * 2 + 1,x,y);
    return ans;
}
signed main()
{
    SPEED;
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    while(q --)
    {
        int op,l,r;
        cin>>op>>l>>r;
        if(op == 1)
        {
            int x;
            cin>>x;
            change_add(1,l,r,x);
        }
        else if(op == 2)
        {
            int x;
            cin>>x;
            change_min(1,l,r,x);
        }
        else
        {
            cout<<ask(1,l,r)<<endl;
        }
    }
    return 0;
}