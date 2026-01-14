#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

int dp[10];
signed main()
{
    SPEED;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        string a;
        cin>>a;
        int len = a.length();
        dp[a[len - 1] - '0'] = max(dp[a[len - 1] - '0'],dp[a[0] - '0'] + 1);
    }
    int ans = 0;
    for(int i=0;i<=9;i++) ans = max(ans,dp[i]);
    cout<<n - ans<<endl;
    return 0;   
}