#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    int sum = 0;
    int max = 0;
    for (int i = 0; i < N; i++) {
        int A;
        std::cin >> A;
        sum += A;
        max = std::max(max, A);
    }
    
    int ans = std::min(sum / 2, sum - max);
    std::cout << ans << "\n";
    
    return 0;
}