#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, a, b;
    std::cin >> n >> a >> b;
    
    b = std::max(b, a);
    int t = std::min(b - a, n);
    i64 ans = 1LL * (b + b - t + 1) * t / 2 + 1LL * a * (n - t);
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