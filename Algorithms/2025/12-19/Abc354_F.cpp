#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> get(const std::vector<int> &a) {
    const int n = a.size();
    
    std::vector<int> f(n);
    std::vector<int> g;
    for (int i = 0; i < n; i++) {
        auto it = std::lower_bound(g.begin(), g.end(), a[i]);
        f[i] = it - g.begin();
        if (it == g.end()) {
            g.push_back(a[i]);
        } else {
            *it = a[i];
        }
    }
    return f;
}

void solve() {
    int N;
    std::cin >> N;
    
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }
    
    auto f = get(A);
    std::reverse(A.begin(), A.end());
    for (auto &x : A) {
        x *= -1;
    }
    auto g = get(A);
    std::reverse(g.begin(), g.end());
    for (int i = 0; i < N; i++) {
        f[i] += g[i];
    }
    int mx = *std::max_element(f.begin(), f.end());
    std::vector<int> ans;
    for (int i = 0; i < N; i++) {
        if (f[i] == mx) {
            ans.push_back(i + 1);
        }
    }
    std::cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << " \n"[i == ans.size() - 1];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int T;
    std::cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}