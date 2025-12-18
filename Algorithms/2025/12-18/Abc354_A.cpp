#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int H;
    std::cin >> H;
    
    std::cout << std::__lg(H + 1) + 1 << "\n";
    
    return 0;
}