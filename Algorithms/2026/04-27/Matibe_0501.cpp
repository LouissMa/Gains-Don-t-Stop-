#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e4 + 10;
int a[N];
int ans[N];
int fa[N];

int find(int x)
{
    if(x != fa[x]) x = find(fa[x]);
    return x;
}

struct Query{
    int l,r,v;
}q[N];
signed main()
{
    SPEED;
    int n,Q;
    cin>>n>>Q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=Q;i++)
    {
        cin>>q[i].l>>q[i].r>>q[i].v;
    }
    for(int i=1;i<=n + 1;i++)
    {
        fa[i] = i;
        ans[i] = a[i];
    }
    for(int i=Q;i>=1;i--)
    {
        int l = q[i].l,r = q[i].r,v = q[i].v;
        int cur = find(l);
        while(cur <= r)
        {
            ans[cur] = v;
            fa[cur] = find(cur + 1);
            cur = find(cur);
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(ans[i] == 0) ans[i] = a[i];
        cout<<ans[i]<<" \n"[i == n];
    }
    return 0;
}