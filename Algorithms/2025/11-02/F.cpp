/*
Problem: Problem Title
Contest: Contest Name
URL: URL
Memory Limit: 1024 MB
Time Limit: 2000 ms

Description:
Paste problem statement here
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

vector<vector<int>> G, G_rev;
// memo: 记忆化数组
vector<int> memo;
// visited: 防止在 DFS 中重复访问 (因为是 DAG，不是树)
vector<bool> visited;

/*
 * DFS + DP 计算可达节点数 (祖先或后代)
 * u: 当前节点
 * graph: 要遍历的图 (G 或 G_rev)
 */
int dfs(int u, const vector<vector<int>>& graph) {
    // 如果已经计算过，直接返回
    if (memo[u] != -1) {
        return memo[u];
    }
    
    // visited 仅用于当前 DFS 路径（虽然对于 DAG 不是必须，但好习惯）
    visited[u] = true;
    
    int count = 0;
    for (int v : graph[u]) {
        if (!visited[v]) {
            // 1 (节点v) + v 的所有后代
            count += 1 + dfs(v, graph);
        }
    }
    
    visited[u] = false;
    
    // 存储并返回结果
    memo[u] = count;
    return count;
}


/*
 * 解决一个测试用例
 */
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    // 1. 初始化图和 DP 辅助数组 (节点 1 到 n)
    G.assign(n + 1, vector<int>());
    G_rev.assign(n + 1, vector<int>());
    
    // 2. 建图
    for (int i = 0; i < n - 1; i++) {
        int u = i + 1; // 节点 i
        int v = i + 2; // 节点 i+1
        if (s[i] == 'L') {
            // v L u (v -> u)
            G[v].push_back(u);
            G_rev[u].push_back(v);
        } else {
            // v R u (u -> v)
            G[u].push_back(v);
            G_rev[v].push_back(u);
        }
    }

    // 3. 计算所有 v 的后代数量 R[v]
    vector<int> R(n + 1);
    memo.assign(n + 1, -1);
    visited.assign(n + 1, false);
    for (int v = 1; v <= n; v++) {
        R[v] = dfs(v, G);
    }

    // 4. 计算所有 v 的祖先数量 L[v]
    vector<int> L(n + 1);
    memo.assign(n + 1, -1);
    visited.assign(n + 1, false);
    for (int v = 1; v <= n; v++) {
        L[v] = dfs(v, G_rev);
    }

    // 5. 使用差分数组统计
    vector<int> diff(n + 1, 0); // 0-indexed 位置
    
    for (int v = 1; v <= n; v++) {
        int min_pos = L[v];
        int max_pos = (n - 1) - R[v];
        
        // C_k 在 [min_pos, max_pos] 区间内都会被 v 贡献 1
        diff[min_pos]++;
        if (max_pos + 1 < n) { // 检查边界
            diff[max_pos + 1]--;
        }
    }

    // 6. 计算前缀和并输出
    int current_count = 0;
    for (int k = 0; k < n; k++) {
        current_count += diff[k];
        cout << current_count << (k == n - 1 ? "" : " ");
    }
    cout << "\n";
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