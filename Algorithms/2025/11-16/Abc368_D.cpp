#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
signed main()
{
    SPEED;
    int n,k;
    cin>>n>>k;
    vector<vector<int>> g(n);
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> f(n),sum(n);
    for(int i=0;i<k;i++)
    {
        int v;
        cin>>v;
        v--;
        f[v] = 1;
    }
    int ans = 0;
    auto dfs = [&](auto &self,int x,int p) -> void{
        sum[x] = f[x];
        int ch = 0;
        if(f[x] == 1)
        {
            ch += 2;
        }
        for(auto y : g[x]){
            if(y == p) continue;
            self(self,y,x);
            sum[x] += sum[y];
            if(sum[y] > 0) ch++;
        }
        if(sum[x] < k) ch++;
        if(ch >= 2) ans++;
    };
    dfs(dfs,0,-1);
    cout<<ans<<endl;
    return 0;
}