#include <bits/stdc++.h>

using i64 = long long;

int parity(const std::vector<int> &a) {
    const int n = a.size();
    std::vector<bool> vis(n);
    int p = n % 2;
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        for (int j = i; !vis[j]; j = a[j]) {
            vis[j] = true;
        }
        p ^= 1;
    }
    return p;
}

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
        b[i]--;
    }
    auto va = a, vb = b;
    std::sort(va.begin(), va.end());
    std::sort(vb.begin(), vb.end());
    if (va != vb) {
        std::cout << "NO\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        a[i] = std::lower_bound(va.begin(), va.end(), a[i]) - va.begin();
    }
    for (int i = 0; i < n; i++) {
        b[i] = std::lower_bound(vb.begin(), vb.end(), b[i]) - vb.begin();
    }
    if (parity(a) != parity(b)) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
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