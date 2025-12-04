#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    std::vector<std::vector<int>> adj(N);
    for (int i = 1; i < N; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    std::vector<int> A(N), cnt(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
        A[i]--;
        cnt[A[i]]++;
    }
    
    std::vector<std::map<int, int>> sub(N);
    std::vector<i64> res(N);
    i64 ans = 0;
    auto dfs = [&](auto &&self, int x, int p) -> void {
        sub[x][A[x]] = 1;
        res[x] = cnt[A[x]] - 1;
        for (auto y : adj[x]) {
            if (y == p) {
                continue;
            }
            self(self, y, x);
            ans += res[y];
            if (sub[y].size() > sub[x].size()) {
                std::swap(sub[x], sub[y]);
            }
            res[x] += res[y];
            for (auto [a, b] : sub[y]) {
                if (sub[x].find(a) != sub[x].end()) {
                    int &v = sub[x][a];
                    res[x] -= 1LL * v * (cnt[a] - v);
                    res[x] -= 1LL * b * (cnt[a] - b);
                    v += b;
                    res[x] += 1LL * v * (cnt[a] - v);
                } else {
                    sub[x][a] = b;
                }
            }
        }
    };
    dfs(dfs, 0, -1);
    
    std::cout << ans << "\n";
    
    return 0;
}
