#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int inf = 1e18;
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    vector<vector<int>> dist(n,vector<int>(n,inf));
    for(int i=0;i<n;i++) dist[i][i]=0;
    vector<int> U(m),V(m),T(m);
    for(int i=0;i<m;i++) 
    {
        cin>>U[i]>>V[i]>>T[i];
        U[i] --;
        V[i] --;
        dist[U[i]][V[i]] = min(dist[U[i]][V[i]],T[i]);
        dist[V[i]][U[i]] = dist[U[i]][V[i]];
    }
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
    int q;
    cin>>q;
    while(q--)
    {
        int k;
        cin>>k;
        vector<int> B(k);
        for(int i=0;i<k;i++)
        {
            cin>>B[i];
            B[i]--;
        }
        sort(B.begin(),B.end());
        int ans = inf;
        do{
            array<int,2> dp;
            int b = B[0];
            // 方案 1: 1 -> ... -> V[b] -> (穿过) -> U[b]
            dp[0] = dist[0][V[b]] + T[b];
            // 方案 2: 1 -> ... -> U[b] -> (穿过) -> V[b]
            dp[1] = dist[0][U[b]] + T[b];
            for(int i=1;i<k;i++)
            {
                int a = B[i-1];
                int b = B[i];
                array<int,2> ndp;
                ndp[0] = min(dp[0] + dist[U[a]][V[b]],dp[1] + dist[V[a]][V[b]]) + T[b];
                ndp[1] = min(dp[0] + dist[U[a]][U[b]],dp[1] + dist[V[a]][U[b]]) + T[b];
                dp = ndp;
            }
            int last = B[k-1];
            ans = min({ans,dp[0] + dist[U[last]][n-1],dp[1] + dist[V[last]][n-1]});
        }while(next_permutation(B.begin(),B.end()));
        cout<<ans<<endl;
    }
    return 0;
}