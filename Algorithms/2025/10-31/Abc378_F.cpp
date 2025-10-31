#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    std::vector<std::vector<int>> adj(N);
    for (int i = 1; i < N; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    std::vector<int> dp(N);
    i64 ans = 0;
    
    auto dfs = [&](auto &&self, int x, int p) -> void {
        dp[x] += (adj[x].size() == 2);
        for (auto y : adj[x]) {
            if (y == p) {
                continue;
            }
            self(self, y, x);
            ans += 1LL * dp[x] * dp[y];
            if (adj[x].size() == 2 && adj[y].size() == 2) {
                ans--;
            }
            if (adj[x].size() == 3) {
                dp[x] += dp[y];
            }
        }
    };
    dfs(dfs, 0, -1);
    
    std::cout << ans << "\n";
    
    return 0;
}