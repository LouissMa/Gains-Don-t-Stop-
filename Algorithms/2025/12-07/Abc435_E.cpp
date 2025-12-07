#include <bits/stdc++.h>
using namespace std;

// 开启 long long，因为 N 最大为 10^9，且运算可能溢出
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n, q;
    cin >> n >> q;

    // 用 set 维护所有不相交的黑色区间，pair 存储 {左端点, 右端点}
    set<PII> st;
    int black_count = 0; // 当前黑色格子的总数

    while(q--) {
        int l, r;
        cin >> l >> r;

        // 1. 找到第一个左端点 >= l 的区间
        auto it = st.lower_bound({l, -1e18});

        // 2. 检查该区间的前一个区间是否与当前 [l, r] 重叠或相邻
        // 比如已有 [1, 2]，现在插入 [3, 4]，因为 2 >= 3-1，所以它们是相邻的，需要合并
        if (it != st.begin()) {
            auto prev = std::prev(it);
            if (prev->second >= l - 1) {
                it = prev; // 如果前一个区间有重叠或相邻，从前一个区间开始处理
            }
        }

        // 维护合并后的新区间范围
        int current_l = l;
        int current_r = r;

        // 3. 遍历并合并所有受影响的区间
        while (it != st.end()) {
            // 如果当前迭代的区间起点 > 新区间终点 + 1，说明后面没有重叠了，退出循环
            // +1 是为了处理相邻的情况，如 [1, 2] 和 [3, 4]
            if (it->first > current_r + 1) break;

            // 更新合并后的区间范围
            current_l = min(current_l, it->first);
            current_r = max(current_r, it->second);

            // 从总计数中减去旧区间的长度
            black_count -= (it->second - it->first + 1);

            // 从集合中删除旧区间，并指向下一个
            it = st.erase(it);
        }

        st.insert({current_l, current_r});
        black_count += (current_r - current_l + 1);
        cout << n - black_count << "\n";
    }

    return 0;
}