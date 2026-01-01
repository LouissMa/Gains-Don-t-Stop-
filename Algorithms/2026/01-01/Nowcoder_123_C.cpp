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

void solve() 
{
    int n,m;
    cin>>n>>m;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    bool ok = true;
    for(int i=1;i<n;i++)
    {
        if(a[i] <= a[i-1])
        {
            ok = false;
            break;
        }
    }
    if(ok)
    {
        cout<<0<<"\n";
        return;
    }
    auto check = [&](int mid) ->bool{
        int cnt = 0;
        for(int i=1;i<n;i++)
        {
            if(a[i] > a[i-1]) continue;
            int d = a[i-1] - a[i] + 1;
            int time = (d + mid - 1) / mid;
            cnt += time;
            if(cnt > m) return false;
        }
        return true;
    };
    int l = 1,r = 1e18;
    int ans = -1;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        if(check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    cout<<ans<<"\n";
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