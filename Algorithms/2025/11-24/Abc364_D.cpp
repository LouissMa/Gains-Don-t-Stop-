#include <bits/stdc++.h>

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, Q;
    std::cin >> N >> Q;
    
    std::vector<int> a(N), b(Q), k(Q);
    for (int i = 0; i < N; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < Q; i++) {
        std::cin >> b[i] >> k[i];
    }
    
    std::sort(a.begin(), a.end());
    
    for (int i = 0; i < Q; i++) {
        int lo = 0, hi = 2E8;
        while (lo < hi) {
            int x = (lo + hi) / 2;
            
            int l = b[i] - x;
            int r = b[i] + x;
            
            int cnt = std::upper_bound(a.begin(), a.end(), r) - std::lower_bound(a.begin(), a.end(), l);
            if (cnt >= k[i]) {
                hi = x;
            } else {
                lo = x + 1;
            }
        }
        std::cout << lo << "\n";
    }
    
    return 0;
}
