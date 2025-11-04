#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, M;
    std::cin >> N >> M;
    
    std::vector<int> f(M, M);
    for (int i = 0; i < N; i++) {
        int L, R;
        std::cin >> L >> R;
        L--;
        R--;
        f[L] = std::min(f[L], R);
    }
    for (int i = M - 2; i >= 0; i--) {
        f[i] = std::min(f[i], f[i + 1]);
    }
    
    i64 ans = 0;
    for (int i = 0; i < M; i++) {
        ans += f[i] - i;
    }
    std::cout << ans << "\n";
    
    return 0;
}