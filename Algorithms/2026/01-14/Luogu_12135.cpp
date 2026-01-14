#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e6+10;
char s[N][2];
int dp[N][2];
signed main()
{
    SPEED;
    string t;
    int n;
    for(int j=0;j<2;j++)
    {
        cin>>t;
        n = t.size();
        for(int i=1;i<=n;i++) s[i][j] = t[i-1];
    }
    // 修正后的边界查找部分
    int st = n+1, en = 0;  // 修改初始值
    for(int i=1;i<=n;i++)
    {
        if(s[i][0] == '#' || s[i][1] == '#')
        {
            st = min(st,i);
            en = max(en,i);
        }
    }
    if(st == n+1)  // 没有找到任何'#'
    {
        cout<<0<<endl;
        return 0;
    }

    // DP初始化也要小心边界
    if(s[st][0] != '#') dp[st][0] = 1; else dp[st][0] = 0;
    if(s[st][1] != '#') dp[st][1] = 1; else dp[st][1] = 0;

    for(int i=st + 1;i <= en;i++)  // 确保这个循环能够正常执行
    {
        int cost0 = (s[i][0] != '#');
        int cost1 = (s[i][1] != '#');
        dp[i][0] = min(dp[i-1][0],dp[i-1][1] + cost1) + cost0;
        dp[i][1] = min(dp[i-1][0] + cost0,dp[i-1][1]) + cost1;
    }
    cout<<min(dp[en][0],dp[en][1])<<endl;
    return 0;
}