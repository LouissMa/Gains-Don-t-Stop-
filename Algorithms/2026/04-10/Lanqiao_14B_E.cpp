#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin>>n;
    string a;
    int ans = 0;
    vector<int> dp(10);
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        int x = a[0] - '0';
        int y = a.back() - '0';
        dp[y] = max(dp[y],dp[x] + 1);
    }
    for(int i=0;i<=9;i++) ans = max(ans,dp[i]);
    cout<<n - ans<<endl;
    return 0;
}