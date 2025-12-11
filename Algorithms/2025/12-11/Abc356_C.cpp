#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, M, K;
    std::cin >> N >> M >> K;
    
    std::vector<int> S(M), R(M);
    for (int i = 0; i < M; i++) {
        int C;
        std::cin >> C;
        
        for (int j = 0; j < C; j++) {
            int X;
            std::cin >> X;
            X--;
            S[i] |= 1 << X;
        }
        
        char r;
        std::cin >> r;
        R[i] = (r == 'o');
    }
    
    int ans = 0;
    for (int s = 0; s < (1 << N); s++) {
        int ok = 1;
        for (int i = 0; i < M; i++) {
            if ((__builtin_popcount(S[i] & s) >= K) != R[i]) {
                ok = 0;
            }
        }
        ans += ok;
    }
    std::cout << ans << "\n";
    
    return 0;
}
