#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,k,b;
    cin>>n>>k>>b;
    vector<int> c(n),s(n);
    for(int i=0;i<n;i++) cin>>c[i]>>s[i];
    vector<vector<int>> dp(k + 1,vector<int>(n,1e18));
    for(int i=0;i<n;i++)
    {
        dp[1][i] = c[i];
    }
    for(int t=2;t<=k;t++)
    {
        for(int i=0;i<n;i++)
        {
            if(dp[t - 1][i] == 1e18) continue;
            for(int j=i + 1;j<n;j++)
            {
                if(s[j] > s[i])
                {
                    dp[t][j] = min(dp[t][j],dp[t - 1][i] + c[j]);
                }
            }
        }
    }
    int ans = 0;
    for(int t = 1;t<=k;t++)
    {
        for(int i=0;i<n;i++)
        {
            if(dp[t][i] <= b)
            {
                ans = max(ans,t);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}