#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 510,INF = 0x3f3f3f3f;
int n,m;
int dist[N];
bool st[N];
int g[N][N];

int Prime()
{
    memset(dist, 0x3f, sizeof dist);  // 初始化所有距离为INF
    int res = 0;                      // 存储最小生成树的权值和
    
    for(int i = 0; i < n; i++)        // 需要加入n个顶点
    {
        // 步骤1：找到距离当前生成树最近的顶点
        int t = -1;
        for(int j = 1; j <= n; j++) {
            if(!st[j] && (t == -1 || dist[t] > dist[j])) {
                t = j;
            }
        }
        
        // 检查是否无法构成生成树（非连通图）
        if(i && dist[t] == INF) return INF;
        
        // 累加边权（第一次加入的顶点无边权）
        if(i) res += dist[t];
        st[t] = true;  // 标记为已加入
        
        // 步骤2：更新其他顶点到生成树的距离
        for(int j = 1; j <= n; j++) {
            dist[j] = min(dist[j], g[t][j]);
        }
    }
    return res;
}

int main()
{
    cin>>n>>m;
    memset(g,0x3f,sizeof g);
    
    while(m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        g[a][b] = g[b][a] = min(g[a][b],c);
    }
    
    int t = Prime();
    if(t == INF) puts("impossible");
    else cout<<t<<endl;
    return 0;
}