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

struct customer{
    int time,l,r;
    bool operator < (const customer& an) const{
        return time < an.time;
    }
}c[110];
void solve() 
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>c[i].time>>c[i].l>>c[i].r;
    sort(c+1,c+n+1);
    int l = m,r = m;
    bool ok = true;
    for(int i=1;i<=n;i++)
    {
        int d = c[i].time - c[i-1].time;
        l -= d;
        r += d;
        l = max(l,c[i].l);
        r = min(r,c[i].r);
        if(l > r)
        {
            ok = false;
            break;
        }
    }
    if(ok) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
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