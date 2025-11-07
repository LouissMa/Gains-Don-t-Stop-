#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, K;
    i64 X;
    std::cin >> N >> K >> X;
    
    std::vector<i64> T(N);
    for (int i = 0; i < N; i++) {
        std::cin >> T[i];
    }
    
    std::vector<i64> cand;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cand.push_back(T[i] + j * X);
        }
    }
    std::sort(cand.begin(), cand.end());
    cand.erase(std::unique(cand.begin(), cand.end()), cand.end());
    
    std::vector dp(cand.size(), std::vector<i64>(N + 1, 1E18));
    std::vector<i64> f(N + 1, 1E18);
    f[0] = 0;
    i64 ans = 1E18;
    for (int i = 0, j = 0; i < cand.size(); i++) {
        i64 d = cand[i];
        while (cand[j] + X <= d) {
            for (int k = 0; k <= N; k++) {
                f[k] = std::min(f[k], dp[j][k]);
            }
            j++;
        }
        int s = 0;
        while (s < N && T[s] <= d) {
            s++;
        }
        for (int j = 0; j <= s; j++) {
            int nj = std::min(s, j + K);
            dp[i][nj] = std::min(dp[i][nj], f[j] + (nj - j) * d);
        }
        ans = std::min(ans, dp[i][N]);
    }
    ans -= std::accumulate(T.begin(), T.end(), 0LL);
    std::cout << ans << "\n";
    
    return 0;
}