#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    vector<string> s(n);
    for(int i=0;i<n;i++)
    {
        cin>>s[i];
    }
    // 使用 set 来存储所有唯一的 M x M 模式
    set<vector<string>> unique_patterns;

    // 1. 遍历所有可能的 M x M 子块的 "左上角行"
    // 左上角行 i 的范围可以从 0 到 n-m
    for (int i = 0; i <= n - m; i++) {
        
        // 2. 遍历所有可能的 M x M 子块的 "左上角列"
        // 左上角列 j 的范围可以从 0 到 n-m
        for (int j = 0; j <= n - m; j++) {
            
            // 3. 构建 M x M 的子网格
            // 创建一个 M 行的 vector 来存储当前模式
            vector<string> pattern(m);

            // 4. 从 (i, j) 开始，提取 M x M 的内容
            for (int r = 0; r < m; r++) {
                // s[i+r] 是原始网格中对应的行
                // .substr(j, m) 从该行的第 j 列开始，提取长度为 m 的子字符串
                pattern[r] = s[i + r].substr(j, m);
            }

            // 5. 将生成的模式插入 set 中，set 会自动处理重复
            unique_patterns.insert(pattern);
        }
    }

    // 6. 输出 set 的大小，即为不同模式的数量
    cout << unique_patterns.size() << endl;
    return 0;
}