#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

constexpr int dx[] = {0, 2, 1, -1, -2, -2, -1, 1, 2};
constexpr int dy[] = {0, 1, 2, 2, 1, -1, -2, -2, -1};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, M;
    std::cin >> N >> M;
    
    std::set<std::array<int, 2>> s;
    i64 ans = 1LL * N * N;
    for (int i = 0; i < M; i++) {
        int a, b;
        std::cin >> a >> b;
        for (int k = 0; k < 9; k++) {
            int x = a + dx[k];
            int y = b + dy[k];
            if (1 <= x && x <= N && 1 <= y && y <= N && s.find({x, y}) == s.end()) {
                ans--;
                s.insert({x, y});
            }
        }
    }
    std::cout << ans << "\n";
    
    return 0;
}