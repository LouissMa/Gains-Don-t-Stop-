#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);

const int MOD = 998244353;

int L[205], R[205];
int cnt[405][405];
vector<int> adj[405];
int dp[2][405][405]; // 滚动数组优化空间

signed main()
{
    SPEED;
    int n;
    if (!(cin >> n)) return 0;
    
    // 1. 坐标离散化
    vector<int> vals;
    for(int i = 0; i < n; ++i) {
        cin >> L[i] >> R[i];
        vals.push_back(L[i]);
        vals.push_back(R[i]);
    }
    
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();
    
    for(int i = 0; i < n; ++i) {
        L[i] = lower_bound(vals.begin(), vals.end(), L[i]) - vals.begin() + 1;
        R[i] = lower_bound(vals.begin(), vals.end(), R[i]) - vals.begin() + 1;
        cnt[L[i]][R[i]]++;
    }
    
    // 提取有效线段加速转移
    for(int i = 1; i <= m; ++i) {
        for(int j = i + 1; j <= m; ++j) {
            if(cnt[i][j]) {
                adj[i].push_back(j);
            }
        }
    }
    
    // 2. 初始化 k=0 (深度为0，仅指空集)
    for(int i = 1; i <= m + 1; ++i) {
        for(int j = 0; j <= m; ++j) {
            dp[0][i][j] = 1;
        }
    }
    
    long long total_sum = dp[0][1][m];
    
    // 3. 开始 DP 状态转移
    for(int k = 1; k <= n; ++k) {
        int cur = k & 1;
        int prv = (k - 1) & 1;
        
        // 当左端点大于右端点时，视作合法空集
        for(int i = 1; i <= m + 1; ++i) {
            for(int j = 0; j < i; ++j) {
                dp[cur][i][j] = 1;
            }
        }
        
        // 枚举区间长度和左端点
        for(int len = 1; len <= m; ++len) {
            for(int i = 1; i <= m - len + 1; ++i) {
                int j = i + len - 1;
                long long ways = dp[cur][i + 1][j]; // 第一种情况：不选从 i 开始的最外层线段
                
                // 第二种情况：选取一条从 i 开始，到 x 结束的最外层线段
                for(int x : adj[i]) {
                    if(x <= j) {
                        long long pick = (1LL * cnt[i][x] * dp[prv][i + 1][x - 1]) % MOD;
                        pick = (pick * dp[cur][x + 1][j]) % MOD;
                        ways = (ways + pick) % MOD;
                    }
                }
                dp[cur][i][j] = ways;
            }
        }
        
        // 累加前缀，方便最后统一换算权值和
        if (k < n) {
            total_sum = (total_sum + dp[cur][1][m]) % MOD;
        }
    }
    
    // 4. 计算结果：N * dp[N] - sum_{k=0}^{N-1} dp[k]
    long long ans = (1LL * n * dp[n & 1][1][m] % MOD - total_sum) % MOD;
    if(ans < 0) ans += MOD;
    
    cout << ans << "\n";
    
    return 0;
}