#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    i64 Sx, Sy, Tx, Ty;
    std::cin >> Sx >> Sy >> Tx >> Ty;
    
    if ((Sy - Sx) % 2 != 0) {
        Sx--;
    }
    if ((Ty - Tx) % 2 != 0) {
        Tx--;
    }
    
    i64 ans = std::abs(Sy - Ty) + std::max(0LL, std::abs(Sx - Tx) - std::abs(Sy - Ty)) / 2;
    std::cout << ans << "\n";
    
    return 0;
}
