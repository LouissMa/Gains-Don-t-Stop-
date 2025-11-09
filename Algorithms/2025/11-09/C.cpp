#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, Q;
    std::cin >> N >> Q;
    
    std::string S;
    std::cin >> S;
    
    int ans = 0;
    for (int j = 0; j < N - 2; j++) {
        ans += (S.substr(j, 3) == "ABC");
    }
    
    for (int i = 0; i < Q; i++) {
        int X;
        char C;
        std::cin >> X >> C;
        X--;
        for (int j = std::max(0, X - 2); j <= std::min(X, N - 3); j++) {
            ans -= (S.substr(j, 3) == "ABC");
        }
        S[X] = C;
        for (int j = std::max(0, X - 2); j <= std::min(X, N - 3); j++) {
            ans += (S.substr(j, 3) == "ABC");
        }
        std::cout << ans << "\n";
    }
    
    return 0;
}