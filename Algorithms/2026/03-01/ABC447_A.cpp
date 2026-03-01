#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, M;
    std::cin >> N >> M;
    
    if (M > (N + 1) / 2) {
        std::cout << "No\n";
    } else {
        std::cout << "Yes\n";
    }
    
    return 0;
}