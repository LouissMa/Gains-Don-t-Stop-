#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

int D, P, C, F;
const int N = 1e5 + 10;
// 初始化 idx = 0 时，h 必须为 -1
int h[N], e[N], ne[N], w[N], idx = 0; 
int dist[N], in[N]; // in 记录入队次数或路径长度
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool SPFA(int x)
{
    // 注意：如果是多组数据或多次调用，每次都要清空
    // 这里的 -0x3f (0xc1c1...) 是一个很小的负数，适合求最大值初始化
    memset(dist, 0xc0, sizeof dist); // 0xc0c0c0c0 约为 -4e18，足够小
    memset(in, 0, sizeof in);
    memset(st, 0, sizeof st);
    
    queue<int> q;
    q.push(x);
    dist[x] = D; // 起点获得工资 D
    st[x] = true;
    in[x] = 1;

    while(q.size())
    {
        int u = q.front();
        q.pop();
        st[u] = false;

        for(int i = h[u]; i != -1; i = ne[i])
        {
            int j = e[i];
            // 松弛操作：求最长路，所以是 < 
            // 现在的钱 < 之前的钱 - 路费 + 工资
            if(dist[j] < dist[u] - w[i] + D) 
            {
                dist[j] = dist[u] - w[i] + D;
                in[j] = in[u] + 1; // 记录路径长度
                if(in[j] > C) return true; // 超过 C 说明有正环

                if(!st[j])
                {
                    st[j] = true;
                    q.push(j);
                }
            }
        }
    }
    return false;
}

signed main()
{
    SPEED;
    // 【关键修正1】初始化邻接表头为 -1
    memset(h, -1, sizeof h); 
    
    cin >> D >> P >> C >> F;
    for(int i = 1; i <= P; i++)
    {
        int u, v;
        cin >> u >> v;
        add(u, v, 0); // 路径不用钱
    }
    for(int i = 1; i <= F; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w); // 航线要钱
    }

    int ans = 0; 
    // ans 初始化问题：如果可能赚不到钱（虽然题目逻辑通常能赚），
    // 最好初始化为一个较小值，不过这题 ans=0 没问题。

    for(int i = 1; i <= C; i++)
    {
        if(SPFA(i))
        {
            cout << "orz\n";
            return 0;
        }
        
        // 【关键修正2】每次跑完 SPFA 都要更新 ans
        // 因为下次循环 SPFA(i+1) 会把 dist 清空
        for(int j = 1; j <= C; j++) 
        {
            // 只要能到达 j (dist 不是负无穷)，就更新答案
            if(dist[j] > -1e18) 
                ans = max(ans, dist[j]);
        }
    }

    cout << ans << endl;
    return 0;
}