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
long long a[200000],b[200000],psum[200001],pref[200001],suf[200001],inf=1000000000000000000LL;
void solve() 
{
    int n,k;
    cin>>n>>k;
    int ans;
    k %= 2;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    psum[0] = 0;
    for(int i=0;i<n;i++) psum[i+1] = psum[i] + a[i];
    for(int i=0;i<=n;i++)
    {
        pref[i] = psum[i];
        suf[i] = psum[i];
    }
    for(int i=0;i<n;i++) pref[i+1] = min(pref[i+1],pref[i]);
    for(int i=n;i>=0;i--) suf[i-1] = max(suf[i-1],suf[i]);
    ans = -inf;
    for(int i=0;i<n;i++)
    {
        ans = max(ans,b[i] * k + suf[i+1] - pref[i]);
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