/*
Problem: Problem Title
Contest: Contest Name
URL: URL
Memory Limit: 1024 MB
Time Limit: 2000 ms

Description:
Paste problem statement here
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

const int N = 2e5 +10;
struct SegTree
{
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
        seg[x] = val;
        while(x)
        {
            seg[x] = max(seg[2 * x],seg[2 * x + 1]);
            x /= 2;
        }
    }
    int query(int g)
    {
        if(seg[1] <g) return -1;
        int x = 1;
        while(x < n)
        {
            if(seg[2 * x] >= g) x = 2 * x;
            else x = 2 * x + 1;
        }
        return x - n;
    }
}bm;
int w[N],c[N];
void solve() 
{
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>w[i];
    for(int i=0;i<m;i++) cin>>c[i];
    bm.init(m);
    for(int i=0;i<m;i++) bm.update(i,c[i]);
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        int now = bm.query(w[i]);
        if(now == -1) continue;
        ans ++;
        bm.update(now,-1);
    }
    cout<<ans<<endl;
}

signed main() 
{
    SPEED;
    int t = 1;
    while(t--) 
    {
        solve();
    }
    return 0;
}