#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

// 使用哈希表存储映射，保证 O(1) 的查询速度
unordered_map<int, string> dict;

signed main()
{
    SPEED;
    int n;
    if (!(cin >> n)) return 0;
    
    // 1. 读取 n 对暗语并存入哈希表
    for(int i = 0; i < n; i++) {
        int p;
        string s;
        cin >> p >> s;
        dict[p] = s;
    }
    
    // 2. 极其关键：吃掉上一个 cin 留下来的换行符
    char ch;
    while (cin.get(ch)) {
        if (ch == '\n') break;
    }
    
    // 3. 读取最后一行长密信
    string line;
    getline(cin, line);
    
    // 4. 遍历密信，边解析边输出
    for (int i = 0; i < line.length(); i++) {
        // 如果遇到 '#'，说明后面跟着的是暗号编号
        if (line[i] == '#') {
            int j = i + 1;
            // 确保 '#' 后面确实有数字
            if (j < line.length() && isdigit(line[j])) {
                int id = 0;
                // 将连续的数字字符提取出来，拼成完整的整数 ID
                while (j < line.length() && isdigit(line[j])) {
                    id = id * 10 + (line[j] - '0');
                    j++;
                }
                // 输出对应的暗语
                cout << dict[id];
                // 让外层循环的 i 直接跳过这段已经解析完的数字
                i = j - 1; 
            } else {
                // 如果 '#' 后面不是数字（虽然题目保证存在，但写上更严谨），原样输出
                cout << '#';
            }
        } else {
            // 普通字符，直接原样输出
            cout << line[i];
        }
    }
    cout << "\n";
    
    return 0;
}