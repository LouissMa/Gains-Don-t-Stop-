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
const int mod = 1e9 + 7;

void solve() 
{
    int n,t;
    cin>>n>>t;
    vector<vector<int>> dp(n+1,vector<int>(n *(n-1)/2 + 1));
    dp[0][0] = 1;
    for(int i=1;i<=n;i++)
    {
        for(int len = 1;len <= i;len++)
        {
            int val = len * (len-1) / 2;
            for(int k=val;k <= t;k++)
            {
                dp[i][k] = (dp[i][k] + dp[i-len][k-val]) % mod;
            }
        }
    }
    cout<<2LL * dp[n][t] % mod<<endl;
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