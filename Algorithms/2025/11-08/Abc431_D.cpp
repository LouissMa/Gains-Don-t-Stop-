#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// 使用 long long 来存储幸福感
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> W(N), H(N), B(N);
    int W_total = 0;
    
    // 读取所有部件并计算总重量
    for (int i = 0; i < N; ++i) {
        cin >> W[i] >> H[i] >> B[i];
        W_total += W[i];
    }

    // dp[w] = 头部重量恰好为 w 时的最大幸福感
    // 初始化为极小的负数，表示不可达
    const i64 INF = -1e18; 
    vector<i64> dp(W_total + 1, INF);

    // 基础状态：头部重量为0时，幸福感为0
    dp[0] = 0;

    // 遍历 N 个部件（物品）
    for (int i = 0; i < N; ++i) {

        // 从 W_total 向下遍历（0/1背包的标准做法）
        for (int w = W_total; w >= 0; --w) {
            // 如果当前状态 dp[w] 本身是不可达的，我们无法从中转移
            if (dp[w] == INF) {
                // 但它可能从 dp[w - W] 转移过来
                if (w >= W[i] && dp[w - W[i]] != INF) {
                    // 2. 放在头上
                    dp[w] = dp[w - W[i]] + H[i];
                }
            } else {
                // dp[w] 是可达的
                
                // 1. 放在身上
                i64 body_choice = dp[w] + B[i];
                
                // 2. 放在头上
                i64 head_choice = INF;
                if (w >= W[i] && dp[w - W[i]] != INF) {
                    head_choice = dp[w - W[i]] + H[i];
                }
                
                dp[w] = max(body_choice, head_choice);
            }
        }
    }

    // 遍历所有可能的头部重量 w
    i64 max_happiness = 0; // 至少可以把所有东西放身上 (w=0)
    for (int w_h = 0; w_h <= W_total; ++w_h) {
        // 检查状态是否可达
        if (dp[w_h] == INF) continue;

        int w_b = W_total - w_h;
        
        // 检查约束：头部重量 <= 身体重量
        if (w_h <= w_b) {
            max_happiness = max(max_happiness, dp[w_h]);
        }
    }

    cout << max_happiness << endl;

    return 0;
}