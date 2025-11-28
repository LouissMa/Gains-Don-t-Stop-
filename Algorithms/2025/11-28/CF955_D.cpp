#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::vector a(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    std::vector b(n + 1, std::vector<int>(m + 1));
    i64 S = 0;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < m; j++) {
            b[i + 1][j + 1] = s[j] == '0' ? 1 : -1;
            S += b[i + 1][j + 1] * a[i][j];
            b[i + 1][j + 1] += b[i + 1][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            b[i][j] += b[i - 1][j];
        }
    }
    int g = 0;
    for (int i = 0; i <= n - k; i++) {
        for (int j = 0; j <= m - k; j++) {
            int d = b[i][j] - b[i][j + k] - b[i + k][j] + b[i + k][j + k];
            g = std::gcd(g, d);
        }
    }
    if (S == 0 || (g != 0 && S % g == 0)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
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
