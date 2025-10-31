#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

constexpr int dx[] = {1, 0, -1, 0};
constexpr int dy[] = {0, 1, 0, -1};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int H, W, K;
    std::cin >> H >> W >> K;
    
    std::vector<std::string> S(H);
    for (int i = 0; i < H; i++) {
        std::cin >> S[i];
    }
    
    std::vector vis(H, std::vector<bool>(W));
    
    int ans = 0;
    auto dfs = [&](auto &&self, int i, int j, int k) {
        if (k == 0) {
            ans++;
            return;
        }
        vis[i][j] = true;
        for (int d = 0; d < 4; d++) {
            int x = i + dx[d];
            int y = j + dy[d];
            if (0 <= x && x < H && 0 <= y && y < W && S[x][y] == '.' && !vis[x][y]) {
                self(self, x, y, k - 1);
            }
        }
        vis[i][j] = false;
    };
    
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (S[i][j] == '.') {
                dfs(dfs, i, j, K);
            }
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}