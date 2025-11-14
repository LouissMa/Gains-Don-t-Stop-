#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string S, T;
    std::cin >> S >> T;
    
    std::vector<std::string> ans;
    const int N = S.size();
    for (int i = 0; i < N; i++) {
        if (S[i] > T[i]) {
            S[i] = T[i];
            ans.push_back(S);
        }
    }
    for (int i = N - 1; i >= 0; i--) {
        if (S[i] < T[i]) {
            S[i] = T[i];
            ans.push_back(S);
        }
    }
    
    std::cout << ans.size() << "\n";
    for (const auto &s : ans) {
        std::cout << s << "\n";
    }
    
    return 0;
}