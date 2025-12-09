#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string S;
    std::cin >> S;
    
    int upper = std::count_if(S.begin(), S.end(), isupper);
    int lower = S.size() - upper;
    for (auto &c : S) {
        if (upper > lower) {
            c = toupper(c);
        } else {
            c = tolower(c);
        }
    }
    std::cout << S << "\n";
    
    return 0;
}