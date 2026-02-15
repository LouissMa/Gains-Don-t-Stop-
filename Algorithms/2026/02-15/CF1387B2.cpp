#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin >> n;
    vector<vector<int>> e(n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        u --;
        v --;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    vector<int> sz(n);
    vector<int> a(n);
    int len = 0;
    function<void(int,int)> dfs = [&](int u,int fa){
        sz[u] = 1;
        a.push_back(u);
        for(auto v : e[u])
        {
            if(v == fa) continue;
            dfs(v,u);
            sz[u] += sz[v];
        }
        len += 2 * min(sz[u],n - sz[u]);
    };
    dfs(0,-1);
    function<int(int,int)> find = [&](int u,int fa){
        for(auto v : e[u])
        {
            if(v == fa) continue;
            if(2 * sz[v] > n) return find(v,u);
        }
        return u;
    };
    int x = find(0,-1);
    a.clear();
    len = 0;
    dfs(x,-1);
    vector<int> ans(n);
    for(int i=0;i<n;i++)
    {
        ans[a[i]] = a[(i + n/2) % n];
    }
    cout<<len<<endl;
    for(int i=0;i<n;i++) cout<<ans[i] + 1<<" \n"[i == n-1];
    return 0;
}