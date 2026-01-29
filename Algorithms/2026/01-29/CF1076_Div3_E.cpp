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
    int n;
    cin>>n;
    vector<int> a(n+1);
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        a[x] ++;
    }
    vector<int> dp(n+1,n+1);
    dp[1] = 0;
    for(int x = 2;x <= n;x++)
    {
        if(!a[x]) continue;
        for(int y = 1;x * y <= n;y++)
        {
            dp[x * y] = min(dp[x * y],dp[y] + 1);
        }
    }
    if(!a[1])
    {
        dp[1] = n + 1;
    }
    else dp[1] = 1;
    for(int i=1;i<=n;i++)
    {
        int ans = dp[i];
        if(ans > n) ans = -1;
        cout<<ans<<" \n"[i==n];
    }
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