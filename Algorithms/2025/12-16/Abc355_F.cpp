#include <bits/stdc++.h>

using i64 = long long;
struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, Q;
    std::cin >> N >> Q;
    
    std::vector dsu(10, DSU(N));
    std::vector cnt(10, N);
    for (int i = 1; i < N; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        a--, b--;
        for (int j = c; j <= 10; j++) {
            cnt[j - 1] -= dsu[j - 1].merge(a, b);
        }
    }
    while (Q--) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--, v--;
        for (int j = w; j <= 10; j++) {
            cnt[j - 1] -= dsu[j - 1].merge(u, v);
        }
        int ans = 0;
        int lst = N;
        for (int j = 1; j <= 10; j++) {
            ans += j * (lst - cnt[j - 1]);
            lst = cnt[j - 1];
        }
        std::cout << ans << "\n";
    }
    
    return 0;
}