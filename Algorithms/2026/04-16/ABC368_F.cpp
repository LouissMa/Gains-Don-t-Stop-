#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }
    
    const int m = *std::max_element(A.begin(), A.end());
    
    std::vector<std::vector<int>> d(m + 1);
    for (int i = 1; i <= m; i++) {
        for (int j = 2 * i; j <= m; j += i) {
            d[j].push_back(i);
        }
    }
    
    std::vector<int> sg(m + 1);
    for (int x = 1; x <= m; x++) {
        const int k = d[x].size();
        std::vector<int> cnt(k + 1);
        for (auto y : d[x]) {
            if (sg[y] <= k) {
                cnt[sg[y]]++;
            }
        }
        while (cnt[sg[x]] > 0) {
            sg[x]++;
        }
    }
    
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans ^= sg[A[i]];
    }
    
    if (ans > 0) {
        std::cout << "Anna\n";
    } else {
        std::cout << "Bruno\n";
    }
    
    return 0;
}