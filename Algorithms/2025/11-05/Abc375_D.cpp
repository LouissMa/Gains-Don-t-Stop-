#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string S;
    std::cin >> S;
    
    int pre[26] {}, suf[26] {};
    for (auto c : S) {
        suf[c - 'A']++;
    }
    
    i64 ans = 0;
    i64 sum = 0;
    for (auto c : S) {
        int x = c - 'A';
        sum -= pre[x];
        suf[x]--;
        ans += sum;
        sum += suf[x];
        pre[x]++;
    }
    std::cout << ans << "\n";
    
    return 0;
}