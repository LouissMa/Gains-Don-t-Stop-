#include <bits/stdc++.h>

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int H, W;
    std::cin >> H >> W;
    
    int X, Y;
    std::cin >> X >> Y;
    X--;
    Y--;
    
    std::vector<std::string> C(H);
    for (int i = 0; i < H; i++) {
        std::cin >> C[i];
    }
    
    std::string S;
    std::cin >> S;
    
    for (auto c : S) {
        int nx = X;
        int ny = Y;
        if (c == 'L') {
            ny--;
        } else if (c == 'R') {
            ny++;
        } else if (c == 'U') {
            nx--;
        } else {
            nx++;
        }
        if (0 <= nx && nx < H && 0 <= ny && ny < W && C[nx][ny] == '.') {
            X = nx;
            Y = ny;
        }
    }
    std::cout << X + 1 << " " << Y + 1 << "\n";
    
    return 0;
}
