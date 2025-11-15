#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    std::vector<std::vector<std::pair<int, int>>> adj(N);
    for (int i = 1; i < N; i++) {
        int U, V, L;
        std::cin >> U >> V >> L;
        U--;
        V--;
        adj[U].emplace_back(V, L);
        adj[V].emplace_back(U, L);
    }
    
    std::vector<i64> a;
    auto dfs = [&](auto &self, int x, int p) -> i64 {
        i64 h = 0;
        for (auto [y, w] : adj[x]) {
            if (y == p) {
                continue;
            }
            i64 v = self(self, y, x) + w;
            if (v > h) {
                std::swap(v, h);
            }
            if (v > 0) {
                a.push_back(v);
            }
        }
        return h;
    };
    a.push_back(dfs(dfs, 0, -1));
    
    a.resize(N);
    std::sort(a.begin(), a.end(), std::greater());
    for (int i = 1; i < N; i++) {
        a[i] += a[i - 1];
    }
    for (int i = 0; i < N; i++) {
        std::cout << 2 * a[i] << "\n";
    }
    
    return 0;
}