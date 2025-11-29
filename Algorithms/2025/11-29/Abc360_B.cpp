#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string S, T;
    std::cin >> S >> T;
    
    for (int w = 1; w < S.size(); w++) {
        for (int c = 0; c < w; c++) {
            std::string t;
            for (int i = c; i < S.size(); i += w) {
                t += S[i];
            }
            if (t == T) {
                std::cout << "Yes\n";
                return 0;
            }
        }
    }
    std::cout << "No\n";
    
    return 0;
}