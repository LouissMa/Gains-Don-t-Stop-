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
    std::vector<int> lst(N, -1);
    i64 ans = 0;
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
        A[i]--;
        ans += 1LL * (i - lst[A[i]]) * (lst[A[i]] + 1);
        lst[A[i]] = i;
    }
    for (int i = 0; i < N; i++) {
        ans += 1LL * (N - lst[i]) * (lst[i] + 1);
    }
    
    std::cout << ans << "\n";
    
    return 0;
}