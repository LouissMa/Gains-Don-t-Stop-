/*
Problem: Macaque's Tree Construction
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

// 全局变量用于记录初始的 t
int original_t;

void solve() 
{
    int x, y;
    cin >> x >> y;
    
    // 严格遵从 Macaque 的神秘要求：如果初始 t = 2，强制让 x + 1
    if (original_t == 2) {
        x++;
    }
    
    // 节点总数
    int n = x + y;
    
    // 判断是否无解
    // 1. 偶数子树的数量绝不可能大于奇数子树的数量 (x > y)
    // 2. 如果总节点 n 为偶数，根节点的子树大小必然是偶数，那么 x 至少为 1
    if (x > y || (n % 2 == 0 && x == 0)) {
        cout << "NO\n";
        return;
    }
    
    cout << "YES\n";
    
    // 我们将所有的节点全部挂在根节点 1 上
    // A 代表我们要挂载的 "长度为 2 的分支 (1-u-v)" 数量
    // B 代表我们要挂载的 "长度为 1 的叶子 (1-w)" 数量
    int A, B;
    
    if (n % 2 != 0) {
        // n 为奇数，根节点本身就是奇数
        A = x;
        B = y - x - 1;
    } else {
        // n 为偶数，根节点本身是偶数
        A = x - 1;
        B = y - x + 1;
    }
    
    int cur = 2; // 分配节点编号，从 2 开始
    
    // 构造 A 个长度为 2 的分支
    for (int i = 0; i < A; i++) {
        int u = cur++;
        int v = cur++;
        cout << 1 << " " << u << "\n";
        cout << u << " " << v << "\n";
    }
    for (int i = 0; i < B; i++) {
        int u = cur++;
        cout << 1 << " " << u << "\n";
    }
}

signed main() 
{
    SPEED;
    int t = 1;
    if (cin >> t) {
        original_t = t; // 记录初始 t 的值
        while(t--) 
        {
            solve();
        }
    }
    return 0;
}