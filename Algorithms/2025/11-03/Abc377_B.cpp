#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    bool r[8] {}, c[8] {};
    for (int i = 0; i < 8; i++) {
        std::string S;
        std::cin >> S;
        
        for (int j = 0; j < 8; j++) {
            if (S[j] == '#') {
                r[i] = true;
                c[j] = true;
            }
        }
    }
    
    int ans = std::count(r, r + 8, false) * std::count(c, c + 8, false);
    std::cout << ans << "\n";
    
    return 0;
}