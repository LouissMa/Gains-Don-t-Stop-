/*
Problem: 单向深渊
Contest: 2025 ICPC Taiwan
URL: URL
Memory Limit: 1024 MB
Time Limit: 2000 ms
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;
const int N = 2e5+10;
int n,m;

void solve() 
{
    cin>>n>>m;
    vector<int> dp(n+1,0);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        int val_u = dp[u];
        int val_v = dp[v];
        dp[u] =val_v + w;
        dp[v] = val_u + w;
    }
    int ans = 0;
    for(int i=1;i<=n;i++)
    {
        ans = max(ans,dp[i]);
    }
    cout<<ans<<endl;
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