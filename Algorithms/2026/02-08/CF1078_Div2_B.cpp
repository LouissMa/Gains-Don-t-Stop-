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
    int n,x,y;
    cin>>n>>x>>y;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    int sum = 0;
    for(int i=0;i<n;i++)
    {
        sum += a[i]/x*y;
    }
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        int cur = sum - a[i]/x*y + a[i];
        ans = max(ans,cur);
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