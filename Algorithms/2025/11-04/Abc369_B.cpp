#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    int ans = 0;
    
    int L = -1, R = -1;
    
    for (int i = 0; i < N; i++) {
        int A;
        char t;
        std::cin >> A >> t;
        
        if (t == 'L') {
            if (L != -1) {
                ans += std::abs(L - A);
            }
            L = A;
        } else {
            if (R != -1) {
                ans += std::abs(R - A);
            }
            R = A;
        }
    }
    std::cout << ans << "\n";
    
    return 0;
}