#include <bits/stdc++.h>
using namespace std;

// 开启 long long，因为坐标和总和都可能很大
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

// 定义一个哨兵值（无穷大），用于表示没有邻居
const int INF = 2e18; // 2 * 10^18

signed main()
{
    SPEED;
    int n;
    cin >> n;
    // total_sum 存储所有 d_i 的总和
    int total_sum = 0;
    // positions 存储数轴上所有人的坐标
    set<int> positions;
    // d_values 存储每个坐标上的人的 d_i (最近邻居距离)
    map<int, int> d_values;

    // 1. 处理第 0 个人
    positions.insert(0);
    d_values[0] = INF; // 初始时没有邻居，设为无穷大

    // 2. 循环处理 N 个人
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        
        // 3. 将新的人 X_i 插入 set
        // .first 获取指向新插入元素的迭代器
        auto it = positions.insert(x).first;

        // 4. 查找左右邻居
        int pos_L = -1, dist_L = INF;
        int pos_R = -1, dist_R = INF;

        // 查找左邻居 (P_L)
        if (it != positions.begin()) {
            // std::prev 获取前一个元素的迭代器
            pos_L = *std::prev(it);
            dist_L = x - pos_L;
        }

        // 查找右邻居 (P_R)
        // std::next 获取后一个元素的迭代器
        if (std::next(it) != positions.end()) {
            pos_R = *std::next(it);
            dist_R = pos_R - x;
        }

        // 5. 计算新的人 (X_i) 的 d_new
        int d_new = min(dist_L, dist_R);
        // 将 d_new 加入总和
        total_sum += d_new;
        // 存储 d_new
        d_values[x] = d_new;

        // 6. 更新左邻居 (P_L) 的 d_i
        if (pos_L != -1) {
            int d_L_old = d_values[pos_L];
            int d_L_new = min(d_L_old, dist_L);
            
            // 更新总和：减去旧值，加上新值
            // (注意：第一次 i=1 时, d_L_old 是 INF, 我们不能减去它)
            if (i == 1) {
                // 这是第一个人，d_0 之前不在总和中，现在要加入
                total_sum += d_L_new; 
            } else {
                total_sum = total_sum - d_L_old + d_L_new;
            }
            d_values[pos_L] = d_L_new;
        }

        // 7. 更新右邻居 (P_R) 的 d_i
        if (pos_R != -1) {
            int d_R_old = d_values[pos_R];
            int d_R_new = min(d_R_old, dist_R);
            // 更新总和
            total_sum = total_sum - d_R_old + d_R_new;
            d_values[pos_R] = d_R_new;
        }

        // 8. 打印当前的总和
        cout << total_sum << "\n";
    }

    return 0;
}