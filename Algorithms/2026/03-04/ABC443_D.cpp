#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

void solve() {
    int N;
    std::cin >> N;
    
    std::vector<int> R(N);
    for (int i = 0; i < N; i++) {
        std::cin >> R[i];
    }
    
    i64 ans = std::accumulate(R.begin(), R.end(), 0LL);
    for (int i = 1; i < N; i++) {
        R[i] = std::min(R[i], R[i - 1] + 1);
    }
    for (int i = N - 2; i >= 0; i--) {
        R[i] = std::min(R[i], R[i + 1] + 1);
    }
    ans -= std::accumulate(R.begin(), R.end(), 0LL);
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int T;
    std::cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}
