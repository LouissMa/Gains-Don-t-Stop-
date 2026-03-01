/*
Problem: Problem Title
Contest: Contest Name
URL: URL
Memory Limit: 1024 MB
Time Limit: 2000 ms

Description:
Paste problem statement here
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

const int inf = 1e9;
void solve() 
{
    int n;
    cin>>n;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        a --;b --;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> dp(n,-inf);
    int ans = 1;
    auto dfs = [&](auto self,int x,int p) -> void{
        if(adj[x].size() >= 3)
        {
            dp[x] = 1;
        }
        for(auto y : adj[x])
        {
            if(y == p) continue;
            self(self,y,x);
            if(adj[x].size() >= 3)
            {
                ans = max(ans,dp[y] + 1);
            }
            if(adj[x].size() >= 4)
            {
                ans = max(ans,dp[y] + dp[x]);
                dp[x] = max(dp[x],dp[y] + 1);
            }
        }
    };
    dfs(dfs,0,-1);  
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