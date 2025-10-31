#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
    }
    
    std::vector<i64> dp(n);
    for (int i = 0; i < n; i++) {
        dp[i] = c[i];
        for (int j = 0; j < i; j++) {
            if (a[i] >= a[j]) {
                dp[i] = std::max(dp[i], dp[j] + c[i]);
            }
        }
    }
    
    i64 ans = std::accumulate(c.begin(), c.end(), 0LL) - *std::max_element(dp.begin(), dp.end());
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}