#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::array<std::vector<int>, 3> a;
    for (int i = 0; i < 3; i++) {
        a[i].resize(n);
    }
    i64 tot = 0;
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < n; i++) {
            std::cin >> a[j][i];
            if (j == 0) {
                tot += a[j][i];
            }
        }
    }
    std::array<int, 3> perm {0, 1, 2};
    do {
        std::array<int, 3> l {}, r {};
        int cur = 0;
        bool ok = true;
        for (int i = 0; i < 3; i++) {
            l[perm[i]] = cur + 1;
            i64 sum = 0;
            while (sum < (tot + 2) / 3 && cur < n) {
                sum += a[perm[i]][cur++];
            }
            if (sum < (tot + 2) / 3) {
                ok = false;
                break;
            }
            r[perm[i]] = cur;
        }
        if (ok) {
            for (int i = 0; i < 3; i++) {
                std::cout << l[i] << " " << r[i] << " \n"[i == 2];
            }
            return;
        }
    } while (std::next_permutation(perm.begin(), perm.end()));
    std::cout << -1 << "\n";
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