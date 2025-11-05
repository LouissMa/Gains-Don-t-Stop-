#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    std::vector<std::string> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }
    
    std::vector B(N, std::string(N, '.'));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x = i, y = j;
            int t = std::min({i + 1, j + 1, N - i, N - j});
            t %= 4;
            while (t--) {
                std::tie(x, y) = std::pair(N - 1 - y, x);
            }
            B[i][j] = A[x][y];
        }
    }
    for (int i = 0; i < N; i++) {
        std::cout << B[i] << "\n";
    }
    
    return 0;
}