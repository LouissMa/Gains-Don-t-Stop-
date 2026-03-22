#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, K;
    std::cin >> N >> K;
    
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
        A[i] %= K;
    }
    
    std::sort(A.begin(), A.end());
    
    int ans = A[0] + K - A[N - 1];
    for (int i = 1; i < N; i++) {
        ans = std::max(ans, A[i] - A[i - 1]);
    }
    ans = K - ans;
    std::cout << ans << "\n";
    
    return 0;
}