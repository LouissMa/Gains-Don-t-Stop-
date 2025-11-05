#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

constexpr int S = 500;
constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    int sum = 0;
    
    std::array<std::array<int, S + 1>, S + 1> dp;
    for (int i = 0; i <= S; i++) {
        dp[i].fill(inf);
    }
    dp[0][0] = 0;
    
    for (int i = 0; i < N; i++) {
        int A, B;
        std::cin >> A >> B;
        
        sum += B;
        std::array<std::array<int, S + 1>, S + 1> ndp {};
        for (int x = 0; x <= S; x++) {
            for (int y = 0; y <= S; y++) {
                ndp[x][y] = inf;
                if (x >= B) {
                    ndp[x][y] = std::min(ndp[x][y], dp[x - B][y] + (A != 1));
                }
                if (y >= B) {
                    ndp[x][y] = std::min(ndp[x][y], dp[x][y - B] + (A != 2));
                }
                ndp[x][y] = std::min(ndp[x][y], dp[x][y] + (A != 3));
            }
        }
        dp = ndp;
    }
    
    int ans = inf;
    if (sum % 3 == 0) {
        sum /= 3;
        ans = dp[sum][sum];
    }
    if (ans == inf) {
        ans = -1;
    }
    std::cout << ans << "\n";
    
    return 0;
}