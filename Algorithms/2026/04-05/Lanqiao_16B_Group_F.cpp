#include <bits/stdc++.h>

using namespace std;

const int inf = 0x3f3f3f3f;

void solve()
{
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size();
    vector<int> sta(n);
    for (int i = 0; i < n; i++)
    {
        if (s1[i] == '#')
            sta[i] |= 1;
        if (s2[i] == '#')
            sta[i] |= 2;
    }
    int L = n,R = -1;
    for(int i=0;i<n;i++)
    {
        if(sta[i] != 0)
        {
            L = min(L,i);
            R = max(R,i);
        }
    }
    if(R == -1)
    {
        cout<<0<<endl;
        return;
    }
    vector<vector<int>> dp(n,vector<int>(4,inf));
    auto calc = [&](int p,int t) -> int{
        int cnt = 0;
        if(t & 1) cnt ++;
        if(t & 2) cnt ++;
        int num = 0;
        if(sta[p] & 1) num ++;
        if(sta[p] & 2) num ++;
        return cnt - num;
    };
    auto check = [&](int x,int t) -> bool{
        return (t & sta[x]) == sta[x] && (t != 0);
    };
    for(int j=1;j<4;j++)
    {
        if(check(L,j)) dp[L][j] = calc(L,j);
    }
    for(int i=L+1;i<=R;i++)
    {
        for(int j=1;j<4;j++)
        {
            if(!check(i,j)) continue;
            int add = calc(i,j);
            for(int k=1;k<4;k++)
            {
                if(!check(i - 1,k)) continue;
                if((k & j) == 0) continue;
                dp[i][j] = min(dp[i][j],dp[i - 1][k] + add);
            }
        }
    }
    int ans = inf;
    for(int j=1;j<4;j++)
    {
        if(check(R,j)) ans = min(ans,dp[R][j]);
    }
    cout<<ans<<endl;
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int _ = 1;
    while (_--)
    {
        solve();
    }
    return 0;
}
