#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,s,t;
    cin>>n>>s>>t;
    vector<int> A(n),B(n),C(n),D(n);
    for(int i=0;i<n;i++) cin>>A[i]>>B[i]>>C[i]>>D[i];
    double ans = INFINITY;
    vector<bool> vis(n);
    auto dfs = [&](auto & self,int x,int y,double sum = 0.0,int c = 0)
    {
        if(c == n)
        {
            ans = min(ans,sum);
            return;
        }
        for(int i=0;i<n;i++)
        {
            if(vis[i]) continue;
            double d1 = hypot(A[i] - x,B[i] - y);
            double d2 = hypot(C[i] - x,D[i] - y);
            double d0 = hypot(A[i] - C[i],B[i] - D[i]);
            vis[i] = true;
            self(self,C[i],D[i],sum + d1/s + d0/t,c + 1);
            self(self,A[i],B[i],sum + d2/s + d0/t,c + 1);
            vis[i] = false;
        }
    };
    dfs(dfs,0,0);
    cout<<fixed<<setprecision(20)<<ans<<"\n";
    return 0;
}