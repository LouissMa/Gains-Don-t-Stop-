#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
const int N = 1e6 + 10;
int n,m,a,b,c;
struct tree
{
    int l,r;
    int pre;
    int add;
}t[N];
void build(int p,int x,int y)
{
    t[p].l = x;
    t[p].r = y;
    if(x == y)
    {
        t[p].pre = 0;
        return;
    }
    int mid = (x + y) >> 1;
    build(2 * p,x,mid);
    build(2 * p + 1,mid + 1,y);
}

void tag(int p)
{
    if(t[p].add == 0) return;
    t[2 * p].pre = (t[2 * p].r - t[2 * p].l + 1) - t[2 * p].pre;
    t[2 * p + 1].pre = (t[2 * p + 1].r - t[2 * p + 1].l + 1) - t[2 * p + 1].pre;
    if(t[2 * p].add == 0) t[2 * p].add = 1;
    else t[2 * p].add = 0;
    if(t[2 * p + 1].add == 0) t[2 * p + 1].add = 1;
    else t[2 * p + 1].add = 0;
    t[p].add = 0;
}

void change(int p,int l,int r)
{
    if(l <= t[p].l && t[p].r <= r)
    {
        t[p].pre = (t[p].r - t[p].l + 1) - t[p].pre;
        if(t[p].add == 0) t[p].add = 1;
        else t[p].add = 0;
        return;
    }
    tag(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if(a <= mid) change(2 * p,l,r);
    if(mid < b) change(2 * p + 1,l,r);
    t[p].pre = t[2 * p].pre + t[2 * p + 1].pre;
}

int ask(int p,int l,int r)
{
    if(l <= t[p].l && t[p].r <= r) return t[p].pre;
    tag(p);
    int mid = (t[p].l + t[p].r) >> 1;
    int ans = 0;
    if(a <= mid) ans += ask(2 * p,l,r);
    if(mid < b) ans += ask(2 * p + 1,l,r);
    return ans;
}
signed main()
{
    SPEED;
    cin>>n>>m;
    build(1,1,n);
    for(int i=0;i<m;i++)
    {
        cin>>c>>a>>b;
        if(c == 0)
        {
            change(1,a,b);
        }
        else
        {
            cout<<ask(1,a,b)<<endl;
        }
    }
    return 0;
}