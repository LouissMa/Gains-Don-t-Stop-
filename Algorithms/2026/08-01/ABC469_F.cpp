#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

// 并查集模板
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true; // 成功合并，说明原本不在一个集合
        }
        return false;
    }
};

signed main() {
    SPEED;

    int N;
    if (!(cin >> N)) return 0;

    int max_A = 0;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        max_A = max(max_A, A[i]);
    }

    // in_A[x] 标记数字 x 是否存在于原数组 A 中
    vector<bool> in_A(max_A + 1, false);
    for (int i = 0; i < N; ++i) {
        in_A[A[i]] = true;
    }

    // 初始化并查集，大小为值域范围
    DSU dsu(max_A);

    int ans = 0;
    int edges_added = 0;

    // 按照边权从大到小枚举，模拟 Kruskal
    for (int d = max_A; d >= 1; --d) {
        int first_multiple = -1;
        
        // 枚举 d 的所有倍数
        for (int m = d; m <= max_A; m += d) {
            if (in_A[m]) {
                if (first_multiple == -1) {
                    // 记录第一个存在的倍数作为基准点
                    first_multiple = m;
                } else {
                    // 尝试将其与基准点合并
                    if (dsu.unite(first_multiple, m)) {
                        ans += d;
                        edges_added++;
                    }
                }
            }
        }
        
        // 如果已经构成了生成树（加入了 N-1 条边），就可以提前结束了
        if (edges_added == N - 1) {
            break;
        }
    }

    cout << ans << "\n";

    return 0;
} 