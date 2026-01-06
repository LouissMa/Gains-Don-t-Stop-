#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int INF = 1e18;  // 对于long long，用大一点的INF
vector<PII> e[N];      // 存储邻接表：e[u] = {v, w}
int dist[N];
bool st[N];
int n, m, s;

void dijkstra() {
    // 初始化
    for(int i = 1; i <= n; i++) {
        dist[i] = INF;
        st[i] = false;
    }
    dist[s] = 0;
    
    // 使用优先队列，存储(distance, vertex)
    // greater<PII> 使优先队列成为最小堆
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({0, s});  // {距离, 节点}
    
    while(!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        
        // 如果已经处理过，跳过
        if(st[u]) continue;
        st[u] = true;
        
        // 遍历所有邻接边
        for(auto& [v, w] : e[u]) {
            if(dist[v] > d + w) {
                dist[v] = d + w;
                q.push({dist[v], v});
            }
        }
    }
}

signed main() {
    SPEED;
    cin >> n >> m >> s;
    
    // 清空邻接表（如果有多个测试用例）
    for(int i = 1; i <= n; i++) {
        e[i].clear();
    }
    
    for(int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        e[a].push_back({b, c});
    }
    
    dijkstra();
    
    for(int i = 1; i <= n; i++) {
        if(dist[i] >= INF) {
            cout << "2147483647 ";  // 题目通常要求输出这个值表示不可达
        } else {
            cout << dist[i] << " \n"[i == n];
        }
    }
    
    return 0;
}