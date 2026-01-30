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
    string s;
    cin>>s;
    s = ' ' + s;
    vector<vector<int>> dp(n + 1, vector<int>(2,1e9));
    for(int i=1;i<=n;i++)
    {
        if(s[i] == '1')
        {
            if(i >= 3 && s[i - 2] == '1')
            {
                dp[i][1] = dp[i-2][1] + 1;
                continue;
            }
            if(i >= 4 && s[i - 3] == '1')
            {
                dp[i][1] =  dp[i-3][1] + 1;
                continue;
            }
            int res = 1e9;
            if(i >= 3) res = min(res,dp[i-2][1]);
            if(i >= 4) res = min(res,dp[i-3][1]);
            if(res == 1e9) res = 0;
            dp[i][1] = res + 1;
        }
        else
        {
            if(s[i-1] != '1' && (i == n || s[i + 1] != '1'))
            {
                if(i >= 3 && s[i - 2] == '1')
                {
                    dp[i][1] = dp[i-2][1] + 1;
                    continue;
                }
                if(i >= 4 && s[i - 3] == '1')
                {
                    dp[i][1] =  dp[i-3][1] + 1;
                    continue;
                }
                int res = 1e9;
                if(i >= 3) res = min(res,dp[i-2][1]);
                if(i >= 4) res = min(res,dp[i-3][1]);
                if(res == 1e9) res = 0;
                dp[i][1] = res + 1;
            }
        }
    }
    cout<<min(dp[n][1],dp[n-1][1])<<endl;
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