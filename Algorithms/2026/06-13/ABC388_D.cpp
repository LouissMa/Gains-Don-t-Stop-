#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }
    
    std::vector<int> d(N), ans(N);
    for (int i = 0; i < N; i++) {
        if (i) {
            d[i] += d[i - 1];
        }
        ans[i] = d[i] + A[i];
        int v = std::min(N - i - 1, ans[i]);
        ans[i] -= v;
        if (i + 1 < N) {
            d[i + 1]++;
        }
        if (i + 1 + v < N) {
            d[i + 1 + v]--;
        }
        std::cout << ans[i] << " \n"[i == N - 1];
    }
    
    return 0;
}