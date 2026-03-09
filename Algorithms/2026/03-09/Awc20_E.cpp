#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

struct segtree{
    int n;
    int seg[1 << 20];
    void init(int x)
    {
        n = 1 << (__lg(x) + 1);
        for(int i=0;i<2 * n;i++) seg[i] = 0;
    }
    void update(int x,int val)
    {
        x += n;
        seg[x] = val,x /= 2;
        while(x)
        {
            seg[x] = max(seg[2 * x],seg[2 * x + 1]);
            x /= 2;
        }
    }
    int quary(int g)
    {
        if(seg[1] < g) return -1;
        int x = 1;
        while(x < n)
        {
            if(seg[2 * x] >= g) x = 2 * x;
            else x = 2 * x + 1;
        }
        return x - n;
    }
}bm;
const int N = 2e5 +10;
int w[N],c[N];
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>w[i];
    for(int i=0;i<m;i++) cin>>c[i];
    bm.init(m);
    for(int i=0;i<m;i++) bm.update(i,c[i]);
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        int now = bm.quary(w[i]);
        if(now == -1) continue;
        ans ++;
        bm.update(now,0);
    }
    cout<<ans<<endl;
    return 0;
}