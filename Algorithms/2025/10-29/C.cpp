#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, M;
    std::cin >> N >> M;
    
    i64 ans = 1LL * N * (N + 1) / 2;
    
    std::vector<int> X(M), A(M);
    for (int i = 0; i < M; i++) {
        std::cin >> X[i];
    }
    for (int i = 0; i < M; i++) {
        std::cin >> A[i];
        ans -= 1LL * X[i] * A[i];
    }
    
    if (std::accumulate(A.begin(), A.end(), 0LL) != N) {
        std::cout << -1 << "\n";
        return 0;
    }
    
    std::vector<int> p(M);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(),
        [&](int i, int j) {
            return X[i] < X[j];
        });
    int sum = 0;
    for (auto i : p) {
        if (X[i] > sum + 1) {
            std::cout << -1 << "\n";
            return 0;
        }
        sum += A[i];
    }
    std::cout << ans << "\n";
    
    return 0;
}