#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        std::cin >> l[i] >> r[i];
        l[i]--;
        r[i]--;
    }
    
    std::vector<int> siz(n), ord, pos(n), p(n);
    const int logn = std::__lg(n);
    std::vector<std::vector<int>> f(logn + 1, std::vector<int>(n));
    auto dfs = [&](auto &&self, int x) -> void {
        f[0][x] = p[x];
        for (int j = 0; j < logn; j++) {
            f[j + 1][x] = f[j][f[j][x]];
        }
        pos[x] = ord.size();
        ord.push_back(x);
        siz[x] = 1;
        if (l[x] != -1) {
            p[l[x]] = p[r[x]] = x;
            self(l[x]);
            ord.push_back(x);
            self(r[x]);
            ord.push_back(x);
            siz[x] += siz[l[x]] + siz[r[x]];
        }
    };
    dfs(0);
    
    std::vector<i64> g(n);
    auto dfs1 = [&](this auto &&self, int x) -> void {
        g[x] += 2 * siz[x] - 1;
        if (l[x] != -1) {
            g[l[x]] = g[r[x]] = g[x];
            self(l[x]);
            self(r[x]);
        }
    };
    dfs1(0);
    
    for (int i = 0; i < n; i++) {
        std::cout << g[i] % 1000000007 << " \n"[i == n - 1];
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
