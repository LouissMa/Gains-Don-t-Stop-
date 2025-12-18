#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int m,s,t;
    cin>>m>>s>>t;
    vector<int> dp(t+1);
    for(int i=1;i<=t;i++)
    {
        if(m >= 10)
        {
            dp[i] = dp[i-1] + 60;
            m-=10;
        }
        else
        {
            dp[i] = dp[i-1];
            m+=4;
        }
    }
    for(int i=1;i<=t;i++)
    {
        if(dp[i] < dp[i-1] + 17)
        {
            dp[i] = dp[i-1] + 17;
        }
        if(dp[i] >= s)
        {
            cout<<"Yes"<<endl<<i<<endl;
            return 0;
        }
    }
    cout<<"No"<<endl;
    cout<<dp[t]<<endl;
    return 0;
}