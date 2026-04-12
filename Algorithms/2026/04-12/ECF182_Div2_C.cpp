/*
Problem: Non-Descending Arrays
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

const int mod = 998244353;
void solve() 
{
    int n;
    cin>>n;
    vector<int> a(n+1);
    vector<int> b(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    vector<vector<int>> dp(2,vector<int>(n+1));
    dp[0][1] = dp[1][1] = 1;
    for(int i=2;i<=n;i++)
    {
        if(a[i] >= a[i-1] && b[i] >= b[i-1])
        {
            dp[0][i] = (dp[0][i] + dp[0][i-1]) % mod;
        }
        if(a[i] >= b[i-1] && b[i] >= a[i-1])
        {
            dp[0][i] = (dp[0][i] + dp[1][i-1]) % mod;
        }
        if(b[i] >= a[i-1] && a[i] >= b[i-1])
        {
            dp[1][i] = (dp[1][i] + dp[0][i-1]) % mod;
        }
        if(b[i] >= b[i-1] && a[i] >= a[i-1])
        {
            dp[1][i] = (dp[1][i] + dp[1][i-1]) % mod;
        }
    }
    cout<<(dp[0][n] + dp[1][n]) % mod<<endl;
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