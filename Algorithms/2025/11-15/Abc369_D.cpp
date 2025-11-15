#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    std::array<i64, 2> dp {0LL, -inf};
    
    for (int i = 0; i < N; i++) {
        int A;
        std::cin >> A;
        
        dp = {std::max(dp[0], dp[1] + 2 * A), std::max(dp[1], dp[0] + A)};
    }
    
    std::cout << std::max(dp[0], dp[1]) << "\n";
    
    return 0;
}