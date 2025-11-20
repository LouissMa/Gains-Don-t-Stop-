#include <bits/stdc++.h>
using namespace std;

// 使用 long long 防止溢出
#define int long long

// 定义三个队列
// q1: 初始蚯蚓
// q2: 切分后的一段（比如较长的一段）
// q3: 切分后的另一段（比如较短的一段）
// 为了方便取队首最大值，手动模拟队列或者使用 STL queue
// 这里因为初始需要排序，q1 用数组模拟指针即可，q2 q3 用 STL queue
int q1[100005]; 
int head1 = 0, tail1 = 0; // q1 的头尾指针
queue<int> q2, q3;

signed main() {
    // 优化 IO
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, q, u, v, t;
    cin >> n >> m >> q >> u >> v >> t;

    // 读入并从大到小排序
    for (int i = 0; i < n; i++) {
        cin >> q1[i];
    }
    sort(q1, q1 + n, greater<int>());
    tail1 = n; // q1 有 n 个元素

    // 模拟 m 秒
    for (int i = 1; i <= m; i++) {
        // 寻找三个队列队首的最大值
        int x1 = -2e18, x2 = -2e18, x3 = -2e18;
        
        if (head1 < tail1) x1 = q1[head1];
        if (!q2.empty()) x2 = q2.front();
        if (!q3.empty()) x3 = q3.front();

        int max_val = max({x1, x2, x3});
        
        // 弹出最大值
        if (max_val == x1) head1++;
        else if (max_val == x2) q2.pop();
        else q3.pop();

        // 计算真实长度
        int real_len = max_val + (i - 1) * q;

        // 输出被切断蚯蚓的长度
        if (i % t == 0) cout << real_len << " ";

        // 计算切分后的长度
        // 注意先乘后除，避免精度问题
        int len1 = real_len * u / v;
        int len2 = real_len - len1;

        // 还原为相对长度放入队列
        // 当前是第 i 秒，新蚯蚓不仅没享受到前 i-1 秒的增长，
        // 也没享受到第 i 秒的增长（因为是第 i 秒切完剩下的）
        // 所以要减去 i * q
        q2.push(len1 - i * q);
        q3.push(len2 - i * q);
    }
    cout << endl; // 第一行结束换行

    // 合并剩余元素，排序输出
    // 这里的元素都是“相对值”，真实值需要加上 m * q
    // 我们可以继续利用单调性，类似归并排序的方式依次取出最大值
    int rank = 0;
    while (head1 < tail1 || !q2.empty() || !q3.empty()) {
        int x1 = -2e18, x2 = -2e18, x3 = -2e18;
        
        if (head1 < tail1) x1 = q1[head1];
        if (!q2.empty()) x2 = q2.front();
        if (!q3.empty()) x3 = q3.front();

        int max_val = max({x1, x2, x3});
        
        if (max_val == x1) head1++;
        else if (max_val == x2) q2.pop();
        else q3.pop();

        rank++;
        if (rank % t == 0) {
            cout << (max_val + m * q) << " ";
        }
    }
    cout << endl;

    return 0;
}