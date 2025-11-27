#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int x, y, k;
    std::cin >> x >> y >> k;
    
    while (x >= y && k > 0) {
        int t = std::min(k, y - x % y);
        k -= t;
        x += t;
        while (x % y == 0) {
            x /= y;
        }
    }
    
    if (x < y) {
        x = (x - 1 + k) % (y - 1) + 1;
    }
    std::cout << x << "\n";
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
