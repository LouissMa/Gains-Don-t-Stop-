#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,x,y;
    cin>>n>>x>>y;
    vector<vector<int>> dp(n+1,vector<int>(x+1,y+1));
    dp[0][0] = 0;
    for(int i=0;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        for(int c = i;c >=0 ;c--)
        {
            for(int d = x;d >= a;d--)
            {
                dp[c + 1][d] = min(dp[c + 1][d],dp[c][d-a] + b);
            }
        }
    }
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        for(int X = 0;X <= x;X++)
        {
            if(dp[i][X] <= y) ans = max(ans,i+1);
        }
    }
    cout<<ans<<endl;
    return 0;
}