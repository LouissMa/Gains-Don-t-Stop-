#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 510, M = 10010;  // N: 最大点数，M: 最大边数
int n, m, k;                    // n: 点数，m: 边数，k: 最多经过的边数
int dist[N], backup[N];         // dist: 当前最短距离，backup: 上一轮备份

// 边的结构体
struct Edge {
    int a, b, c;  // 从 a 到 b，权值为 c
} edges[M];

// Bellman-Ford 主函数
void bellman_ford() {
    // 1. 初始化
    memset(dist, 0x3f, sizeof dist);  // 所有距离设为无穷大
    dist[1] = 0;                       // 起点距离为 0
    
    // 2. 迭代 k 次（每次代表"多用一条边"）
    for(int i = 0; i < k; i++) {
        // ⭐ 关键：备份当前状态，防止串联更新
        memcpy(backup, dist, sizeof dist);
        
        // 3. 遍历所有边，进行松弛
        for(int j = 0; j < m; j++) {
            auto t = edges[j];  // 当前边：t.a → t.b，权值 t.c
            // 用 backup[t.a]（上一轮结果）更新 dist[t.b]
            dist[t.b] = min(dist[t.b], backup[t.a] + t.c);
        }
    }
}

int main() {
    cin >> n >> m >> k;
    
    // 读入所有边
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i] = {a, b, c};  // 存储边
    }
    
    // 运行 Bellman-Ford
    bellman_ford();
    
    // 4. 输出结果
    // 注意：判断条件是 > 0x3f3f3f3f/2，不是 == 0x3f3f3f3f
    // 原因：负权边可能让"无穷大"稍微变小，但仍不可达
    if(dist[n] > 0x3f3f3f3f / 2) 
        puts("impossible");
    else 
        cout << dist[n] << endl;
    
    return 0;
}