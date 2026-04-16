#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, M, X0;
    std::cin >> N >> M >> X0;
    
    std::vector<int> A(M), B(M), S(M), T(M);
    for (int i = 0; i < M; i++) {
        std::cin >> A[i] >> B[i] >> S[i] >> T[i];
        A[i]--;
        B[i]--;
    }
    
    std::vector<std::array<int, 3>> e(2 * M);
    for (int i = 0; i < M; i++) {
        e[2 * i] = {S[i], 1, i};
        e[2 * i + 1] = {T[i], 0, i};
    }
    
    std::sort(e.begin(), e.end());
    
    std::vector<int> X(M);
    std::vector<int> tm(N);
    X[0] = X0;
    for (auto [t, o, i] : e) {
        if (o == 1) {
            X[i] = std::max(X[i], tm[A[i]] - S[i]);
        } else {
            tm[B[i]] = std::max(tm[B[i]], T[i] + X[i]);
        }
    }
    
    for (int i = 1; i < M; i++) {
        std::cout << X[i] << " \n"[i == M - 1];
    }
    
    return 0;
}