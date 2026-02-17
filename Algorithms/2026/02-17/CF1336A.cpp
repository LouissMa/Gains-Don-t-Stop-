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
    vector<vector<int>> e(n);
    vector<int> dep(n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        u --;
        v --;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    vector<int> val(n);
    function<int(int,int,int)> dfs = [&](int u,int fa,int d){
        int sz = 1;
        for(auto v : e[u])
        {
            if(v == fa) continue;
            sz += dfs(v,u,d + 1);
        }
        val[u] = d + 1 - sz;
        return sz;
    };
    dfs(0,-1,0);
    sort(val.begin(),val.end(),greater<int>());
    cout<<accumulate(val.begin(),val.begin() + k,0LL)<<endl;
    return 0;
}