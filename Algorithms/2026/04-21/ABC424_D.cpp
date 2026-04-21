#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

int h,w;

void solve() 
{
    cin >> h >> w;
    vector<string> s(h);
    int total_black = 0;
    for(int i=0; i<h; ++i) {
        cin >> s[i];
        for(char c : s[i]) {
            if (c == '#') {
                total_black++;
            }
        }
    }
    if (h > w) {
        vector<string> ns(w, string(h, '.'));
        for(int i=0; i<h; ++i) {
            for(int j=0; j<w; ++j) {
                ns[j][i] = s[i][j];
            }
        }
        s = ns;
        swap(h, w);
    }

    vector<int> cols(w, 0);
    for(int j=0; j<w; ++j) {
        for(int i=0; i<h; ++i) {
            if (s[i][j] == '#') {
                cols[j] |= (1 << i);
            }
        }
    }

    vector<vector<int>> dp(w + 1, vector<int>(1 << h, -1));
    dp[0][0] = 0;

    for (int j = 0; j < w; ++j) {
        for (int mask_cur = 0; mask_cur < (1 << h); ++mask_cur) {
            // 剪枝：当前状态必须是原始列状态的子集
            if ((mask_cur & cols[j]) != mask_cur) continue;

            for (int mask_prev = 0; mask_prev < (1 << h); ++mask_prev) {
                if (dp[j][mask_prev] == -1) continue; // 前一状态不可达

                // 检查转移是否合法
                bool ok = true;
                for (int i = 0; i < h - 1; ++i) {
                    int p1 = (mask_prev >> i) & 1;
                    int p2 = (mask_prev >> (i+1)) & 1;
                    int c1 = (mask_cur >> i) & 1;
                    int c2 = (mask_cur >> (i+1)) & 1;
                    if (p1 && p2 && c1 && c2) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    dp[j+1][mask_cur] = max(dp[j+1][mask_cur], dp[j][mask_prev] + __builtin_popcount(mask_cur));
                }
            }
        }
    }

    int max_kept = 0;
    for(int mask = 0; mask < (1 << h); ++mask) {
        max_kept = max(max_kept, dp[w][mask]);
    }

    cout << total_black - max_kept<<" ";
}

signed main() 
{
    SPEED;
    int t = 1;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}