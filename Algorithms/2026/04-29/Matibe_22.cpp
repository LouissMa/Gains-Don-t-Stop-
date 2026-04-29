#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);

signed main()
{
    SPEED;
    string s;
    if (!(cin >> s)) return 0;
    
    // 开一个大小为 256 的数组来统计所有 ASCII 字符的出现次数
    vector<int> cnt(256, 0);
    for (char c : s) {
        cnt[c]++;
    }
    
    // 计算能拼出大写 MATIJI 的最大数量
    // 注意 'I' 需要 2 个，所以可用组数是 cnt['I'] / 2
    int max_upper = cnt['M'];
    max_upper = min(max_upper, cnt['A']);
    max_upper = min(max_upper, cnt['T']);
    max_upper = min(max_upper, cnt['I'] / 2);
    max_upper = min(max_upper, cnt['J']);
    
    // 计算能拼出小写 matiji 的最大数量
    // 注意 'i' 需要 2 个，所以可用组数是 cnt['i'] / 2
    int max_lower = cnt['m'];
    max_lower = min(max_lower, cnt['a']);
    max_lower = min(max_lower, cnt['t']);
    max_lower = min(max_lower, cnt['i'] / 2);
    max_lower = min(max_lower, cnt['j']);
    
    // 按照格式输出
    cout << max_upper << " " << max_lower << "\n";
    
    return 0;
}