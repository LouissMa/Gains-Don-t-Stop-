#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string S, T;
    std::cin >> S >> T;
    
    std::vector<int> f, g;
    std::string a, b;
    
    int j = -1;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] != 'A') {
            a += S[i];
            f.push_back(i - j - 1);
            j = i;
        }
    }
    f.push_back(S.size() - j - 1);
    
    j = -1;
    for (int i = 0; i < T.size(); i++) {
        if (T[i] != 'A') {
            b += T[i];
            g.push_back(i - j - 1);
            j = i;
        }
    }
    g.push_back(T.size() - j - 1);
    
    if (a != b) {
        std::cout << -1 << "\n";
    } else {
        int ans = 0;
        for (int i = 0; i < f.size(); i++) {
            ans += std::abs(f[i] - g[i]);
        }
        std::cout << ans << "\n";
    }
    
    return 0;
}