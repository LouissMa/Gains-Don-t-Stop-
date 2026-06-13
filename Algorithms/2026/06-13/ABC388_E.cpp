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
    
    int ans = N / 2;
    for (int i = 0, j = 0; i < ans; i++) {
        while (j < N && A[j] < 2 * A[i]) {
            j++;
        }
        int res = i + N - j;
        if (res < i + 1) {
            ans = i;
            break;
        }
        if (res < ans) {
            ans = res;
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}