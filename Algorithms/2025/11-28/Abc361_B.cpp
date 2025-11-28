#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::array<int, 12> a;
    for (int i = 0; i < 12; i++) {
        std::cin >> a[i];
    }
    
    for (int i = 0; i < 3; i++) {
        if (std::max(a[i], a[i + 6]) >= std::min(a[i + 3], a[i + 9])) {
            std::cout << "No\n";
            return 0;
        }
    }
    std::cout << "Yes\n";
    
    return 0;
}