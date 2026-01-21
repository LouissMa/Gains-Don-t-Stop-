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
int a[N],b[N],ans[N],pl[N],pr[N],inf = 1e18;

int check(int n,int dl,int dr)
{
    int l,r;
    l = 0,r = n+1;
    while(r - l > 1)
    {
        int mid = (l + r) >> 1;
        if(pl[mid] >= dl || pr[mid] >= dr) r = mid;
        else l = mid;
    }
    return l;
}
void solve() 
{
    int n,m,q;
    cin>>n>>m>>q;
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a,a+n);
    for(int i=0;i<m;i++) cin>>b[i];
    sort(b,b+m);
    pl[0] = 0;
    pr[0] = 0;
    int c = 0;
    string s;
    cin>>s;
    for(int i=0;i<q;i++)
    {
        if(s[i] == 'L') c--;
        else c ++;
        pl[i + 1] = max(pl[i],-c);
        pr[i+1] = max(pr[i],c);
    }
    for(int i=0;i<=q;i++) ans[i] = 0;
    int l,r;
    for(int i=0;i<n;i++)
    {
        int x = upper_bound(b,b + m,a[i]) - b;
        if(x >= m) r = inf;
        else r = b[x] - a[i];
        x--;
        if(x < 0) l = inf;
        else l = a[i] - b[x];
        ans[check(q,l,r)]++;
    }
    for(int i=q;i>0;i--) ans[i - 1] += ans[i];
    for(int i=1;i<=q;i++) cout<<ans[i]<<" \n"[i==q];
}

signed main() 
{
    SPEED;
    int t = 1;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}