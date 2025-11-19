#include <bits/stdc++.h>

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    std::vector A(N + 1, std::vector(N + 1, std::vector<int>(N + 1)));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                std::cin >> A[i][j][k];
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                A[i][j][k] += A[i - 1][j][k];
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                A[i][j][k] += A[i][j - 1][k];
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                A[i][j][k] += A[i][j][k - 1];
            }
        }
    }
    
    int Q;
    std::cin >> Q;
    
    while (Q--) {
        int Lx, Rx, Ly, Ry, Lz, Rz;
        std::cin >> Lx >> Rx >> Ly >> Ry >> Lz >> Rz;
        Lx--;
        Ly--;
        Lz--;
        
        int ans = A[Rx][Ry][Rz] - A[Rx][Ry][Lz] - A[Rx][Ly][Rz] - A[Lx][Ry][Rz] + A[Rx][Ly][Lz] + A[Lx][Ry][Lz] + A[Lx][Ly][Rz] - A[Lx][Ly][Lz];
        std::cout << ans << "\n";
    }
    
    return 0;
}