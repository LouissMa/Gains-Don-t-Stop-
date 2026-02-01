#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e4 + 10;
// dp数组大小取决于w，w最大10^4
int dp[N]; 
int n, m, w;
int c[N], d[N]; // c是价钱，d是价值

struct DSU {
    vector<int> f;
    DSU() {}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        f.resize(n + 1); // 修正：大小开到 n+1，因为下标从1开始
        iota(f.begin(), f.end(), 0);
    }
    
    // 标准的路径压缩递归写法
    int find(int x) {
        if (f[x] != x) f[x] = find(f[x]);
        return f[x];
    }

    // 修改 merge：合并集合的同时，合并价钱和价值
    bool merge(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy) {
            return false;
        }
        // 将 fy 合并到 fx
        f[fy] = fx; 
        // 核心逻辑：累加价钱和价值到根节点
        c[fx] += c[fy];
        d[fx] += d[fy];
        return true;
    }
};
signed main()
{
    SPEED;
    cin>>n>>m>>w;
    for(int i=1;i<=n;i++) cin>>c[i]>>d[i];
    DSU dsu(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        dsu.merge(u, v);
    }
    for(int i=1;i<=n;i++)
    {
        if(dsu.find(i) == i)
        {
            int cost = c[i];
            int val = d[i];
            for(int j=w;j>=cost;j--)
            {
                dp[j] = max(dp[j],dp[j-cost] + val);
            }
        }
    }
    cout<<dp[w]<<endl;
    return 0;
}