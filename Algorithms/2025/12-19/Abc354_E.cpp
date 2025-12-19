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
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin>>a[i]>>b[i];
    vector<int> adj(n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(a[i] == a[j] || b[i] == b[j])
            {
                adj[i] |= (1 << j);
            }
        }
    }
    vector<int> dp(1 << n),f(1 << n);
    for(int s=0;s<(1 << n);s++)
    {
        for(int i=0;i<n;i++)
        {
            if((s >> i & 1) && !dp[s ^ (1 << i)])
            {
                f[s] |= 1 << i;
            }
        }
        for(int i=0;i<n;i++)
        {
            if(s >> i & 1)
            {
                if(adj[i] & f[s ^ (1 << i)])
                {
                    dp[s] = 1;
                    break;
                }
            }
        }
    }
    cout<<(dp[(1 << n) - 1] ?"Takahashi" : "Aoki")<<"\n";
    return 0;
}