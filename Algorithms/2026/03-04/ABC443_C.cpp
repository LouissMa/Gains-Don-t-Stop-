#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, T;
    std::cin >> N >> T;
    
    int open = 0;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int A;
        std::cin >> A;
        
        if (A < open) {
            continue;
        }
        ans += A - open;
        open = A + 100;
    }
    
    ans += std::max(0, T - open);
    std::cout << ans << "\n";
    
    return 0;
}
