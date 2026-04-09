#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,w;
    cin>>n>>w;
    vector<PII> v;//<长度，数量>
    for(int i=1;i<=n;i++)
    {
        int l,c;
        cin>>l>>c;
        int s = 1;
        while(c)
        {
            int use = min(s,c);
            v.emplace_back(l,use);
            c -= use;
            s *= 2;
        }
    }
    int maxx = 1e18;
    vector<int> dp(w+1,maxx);
    dp[0] = 0;
    for(auto [l,c] : v )
    {
        int len = l * c;
        for(int j=w;j>=0;j--)
        {
            if(j - len >= 0)
            {
                dp[j] = min(dp[j],dp[j - len] + c);
            }
        }
    }
    if(dp[w] == maxx) cout<<-1<<endl;
    else cout<<dp[w]<<endl;
    return 0;
}