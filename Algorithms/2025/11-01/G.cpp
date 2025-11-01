#include <bits/stdc++.h>

using namespace std;

#define int long long // 使用 long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);

// 使用 __builtin_popcountll 来计算 long long 中 1 的个数
int popcount(long long x) {
    return __builtin_popcountll(x);
}

// 线段树节点
struct Node {
    long long mask_or, mask_and;
    long long lazy_or, lazy_and;
    int max_popcount;
    int count_max;
    int l, r; // 节点代表的范围 [l, r]
};

vector<Node> tree;

// 合并两个子节点的结果
void merge(int v) {
    Node& left = tree[2 * v];
    Node& right = tree[2 * v + 1];
    
    // 合并 mask_or 和 mask_and
    tree[v].mask_or = left.mask_or | right.mask_or;
    tree[v].mask_and = left.mask_and | right.mask_and;

    // 合并 max_popcount 和 count_max
    if (left.max_popcount > right.max_popcount) {
        tree[v].max_popcount = left.max_popcount;
        tree[v].count_max = left.count_max;
    } else if (right.max_popcount > left.max_popcount) {
        tree[v].max_popcount = right.max_popcount;
        tree[v].count_max = right.count_max;
    } else {
        tree[v].max_popcount = left.max_popcount;
        tree[v].count_max = left.count_max + right.count_max;
    }
}

// [修正] 将更新 (or_val, and_val) 应用到节点 v
// 此函数不再调用 push_down 或 merge
void apply(int v, long long or_val, long long and_val) {
    Node& T = tree[v];

    // 1. 更新 mask
    T.mask_or = (T.mask_or & and_val) | or_val;
    T.mask_and = (T.mask_and & and_val) | or_val;

    // 2. 更新 lazy 标记
    T.lazy_or = (T.lazy_or & and_val) | or_val;
    T.lazy_and = (T.lazy_and & and_val);
    
    // 3. 检查 S-Beats 优化条件
    if (T.mask_or == T.mask_and) {
        // 所有元素都相同了
        T.max_popcount = popcount(T.mask_or);
        T.count_max = T.r - T.l + 1; // 区间大小
    }
    // 如果 S-Beats 失败，v 的 max_popcount 暂时是旧的，
    // 它将在 update/query 递归返回时的 merge 步骤中被修正。
}

// [修正] 向下推送懒惰标记
void push_down(int v) {
    if (tree[v].l == tree[v].r) return; // 叶节点
    if (tree[v].lazy_or == 0 && tree[v].lazy_and == -1LL) return; // 无标记

    // 将 v 的 lazy 标记应用到子节点
    apply(2 * v, tree[v].lazy_or, tree[v].lazy_and);
    apply(2 * v + 1, tree[v].lazy_or, tree[v].lazy_and);

    // 重置 v 的懒惰标记
    tree[v].lazy_or = 0;
    tree[v].lazy_and = -1LL;
}

// 构建线段树 (不变)
void build(int v, int l, int r) {
    tree[v].l = l;
    tree[v].r = r;
    tree[v].lazy_or = 0;
    tree[v].lazy_and = -1LL;
    
    if (l == r) {
        tree[v].mask_or = 0;
        tree[v].mask_and = 0;
        tree[v].max_popcount = 0;
        tree[v].count_max = 1;
    } else {
        int m = (l + r) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        merge(v);
    }
}

// [修正] 范围更新
void update(int v, int ql, int qr, long long or_val, long long and_val) {
    // 1. 必须先 push_down
    push_down(v); 

    if (tree[v].l > qr || tree[v].r < ql) {
        return; // 完全在范围外
    }
    if (ql <= tree[v].l && tree[v].r <= qr) {
        apply(v, or_val, and_val); // 完全在范围内
        return;
    }
    
    // 2. push_down 已在顶部完成
    int m = (tree[v].l + tree[v].r) / 2;
    update(2 * v, ql, qr, or_val, and_val);
    update(2 * v + 1, ql, qr, or_val, and_val);
    
    // 3. 从子节点更新
    merge(v); 
}

// [修正] 范围查询
pair<int, int> query(int v, int ql, int qr) {
    // 1. 必须先 push_down
    push_down(v); 

    if (tree[v].l > qr || tree[v].r < ql) {
        return {-1, 0}; // 无效值
    }
    if (ql <= tree[v].l && tree[v].r <= qr) {
        return {tree[v].max_popcount, tree[v].count_max};
    }

    // 2. push_down 已在顶部完成
    int m = (tree[v].l + tree[v].r) / 2;
    pair<int, int> left_res = query(2 * v, ql, qr);
    pair<int, int> right_res = query(2 * v + 1, ql, qr);

    // 合并查询结果
    if (left_res.first > right_res.first) {
        return left_res;
    } else if (right_res.first > left_res.first) {
        return right_res;
    } else {
        return {left_res.first, left_res.second + right_res.second};
    }
}


signed main()
{
    SPEED;
    int n, q;
    cin >> n >> q;

    // 调整线段树大小
    tree.resize(4 * n + 5);
    build(1, 1, n); // 1-indexed

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            long long or_val = (1LL << (x - 1));
            long long and_val = -1LL; // ~0LL
            update(1, l, r, or_val, and_val);
        } else if (type == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            long long or_val = 0;
            long long and_val = ~(1LL << (x - 1));
            update(1, l, r, or_val, and_val);
        } else {
            int l, r;
            cin >> l >> r;
            pair<int, int> result = query(1, l, r);
            cout << result.first << " " << result.second << "\n";
        }
    }
    return 0;
}