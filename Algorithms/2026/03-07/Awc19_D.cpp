#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m,t;
    cin>>n>>m>>t;
    int ans = 0;
    vector<PII> p;
    for(int i=0;i<n;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        if(b >= t) ans += a;
        else p.push_back({a,c});
    }
    int s = p.size();
    vector<vector<int>> dp(s + 1, vector<int>(m + 1, 0));
    dp[0][0] = 0;
    for(int i=1;i<=s;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j] = max(dp[i][j],dp[i - 1][j]);
            if(j >= p[i - 1].second)
            {
                dp[i][j] = max(dp[i][j],dp[i - 1][j - p[i-1].second] + p[i-1].first);
            }
        }
    }
    int res = 0;
    for(int i=0;i<=m;i++) res = max(res,dp[s][i]);
    cout<<ans + res<<endl;
    return 0;
}