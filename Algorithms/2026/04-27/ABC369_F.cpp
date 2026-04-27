#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int H, W, N;
    std::cin >> H >> W >> N;
    
    std::vector<int> R(N), C(N);
    for (int i = 0; i < N; i++) {
        std::cin >> R[i] >> C[i];
        R[i]--;
        C[i]--;
    }
    
    std::vector<int> ord(N);
    std::iota(ord.begin(), ord.end(), 0);
    std::sort(ord.begin(), ord.end(),
        [&](int i, int j) {
            return R[i] != R[j] ? R[i] < R[j] : C[i] < C[j];
        });
    std::vector<int> dp(N), f;
    for (auto i : ord) {
        auto it = std::upper_bound(f.begin(), f.end(), C[i]);
        dp[i] = it - f.begin() + 1;
        if (it == f.end()) {
            f.push_back(C[i]);
        } else {
            *it = C[i];
        }
    }
    
    std::cout << f.size() << "\n";
    
    int x = std::find(dp.begin(), dp.end(), f.size()) - dp.begin();
    int r = R[x], c = C[x];
    int res = dp[x];
    std::vector<int> ans;
    for (int i = N - 1; i >= 0; i--) {
        int j = ord[i];
        if (R[j] <= r && C[j] <= c && dp[j] == res) {
            res--;
            ans.push_back(j);
            r = R[j];
            c = C[j];
        }
    }
    std::reverse(ans.begin(), ans.end());
    
    x = 0;
    int y = 0;
    std::string s;
    for (auto i : ans) {
        int nx = R[i], ny = C[i];
        while (x < nx) {
            x++;
            s += 'D';
        }
        while (y < ny) {
            y++;
            s += 'R';
        }
    }
    int nx = H - 1, ny = W - 1;
    while (x < nx) {
        x++;
        s += 'D';
    }
    while (y < ny) {
        y++;
        s += 'R';
    }
    std::cout << s << "\n";
    
    return 0;
}