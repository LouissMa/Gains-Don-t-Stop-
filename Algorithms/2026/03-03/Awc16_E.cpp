#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    vector<int> p(n);
    for(int i=0;i<n;i++) cin>>p[i];
    int s,t;
    cin>>s>>t;
    s --;t --;
    vector<vector<PII>> e(n);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        u--;
        v--;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    vector<vector<int>> dp(n,vector<int>(1 << n,INT_MIN));
    queue<PII> q;
    dp[s][1 << s] = p[s];
    q.emplace(s, 1 << s);
    while(!q.empty())
    {
        auto [u,mask] = q.front();
        q.pop();
        for(auto [v,w] : e[u])
        {
            int nmask = mask | (1 << v);
            if(mask & (1 << v))
            {
                if(dp[u][mask] - w > dp[v][nmask])
                {
                    dp[v][nmask] = dp[u][mask] - w;
                    q.emplace(v, nmask);
                }
            }
            else if(!(mask & (1 << v)))
            {
                if(dp[u][mask] - w + p[v] > dp[v][nmask])
                {
                    dp[v][nmask] = dp[u][mask] - w + p[v];
                    q.emplace(v, nmask);
                }
            }
        }
    }
    cout<<*max_element(dp[t].begin(), dp[t].end())<<endl;
    return 0;
}