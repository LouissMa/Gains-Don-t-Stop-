#include <bits/stdc++.h>

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int A, B, C;
    std::cin >> A >> B >> C;
    
    if ((A - B + 24) % 24 > (C - B + 24) % 24) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    
    return 0;
}                              