#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }
    
    i64 ans = 0;
    for (int i = 0, j = 0; i < N; i++) {
        while (j + 1 < N && A[j + 1] - A[j] == A[i + 1] - A[i]) {
            j++;
        }
        ans += j - i + 1;
    }
    std::cout << ans << "\n";
    
    return 0;
}