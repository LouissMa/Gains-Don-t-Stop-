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

vector<int> compute_lps(const string& pat) {
    int m = pat.length();
    vector<int> lps(m, 0);
    int len = 0; // 上一个最长前缀后缀的长度
    int i = 1;

    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                // 回退到上一个可能匹配的位置
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

/*
 * KMP 算法：在 txt 中搜索 pat
 * 复杂度: O(N + M), N = txt.length(), M = pat.length()
 * 返回: 第一次匹配的起始索引，如果未找到则返回 -1
 */
int kmp_search(const string& txt, const string& pat) {
    int n = txt.length();
    int m = pat.length();
    
    // 模式串为空，总是在 0 位置匹配
    if (m == 0) return 0; 
    
    // 1. 预处理 pat
    vector<int> lps = compute_lps(pat);
    
    int i = 0; // txt 的索引
    int j = 0; // pat 的索引
    
    while (i < n) {
        if (pat[j] == txt[i]) {
            i++;
            j++;
        }
        
        // 匹配成功
        if (j == m) {
            // 我们找到了一个匹配
            // 匹配的起始位置是 i - j
            return (i - j);
            
            // 如果要找所有匹配，则继续：
            // j = lps[j - 1]; 
        } 
        // 匹配失败
        else if (i < n && pat[j] != txt[i]) {
            if (j != 0) {
                // 利用 lps 数组回退 j，i 不动
                j = lps[j - 1];
            } else {
                // j 已经是 0，无法回退，只能移动 i
                i++;
            }
        }
    }
    
    // 遍历完 txt 都没找到
    return -1;
}

/*
 * 解决一个测试用例
 */
void solve() {
    string a, b;
    cin >> a >> b;

    int n = a.length();
    
    // 1. 检查字符数 (O(N) 的快筛，仍然有用)
    int countA_0 = 0;
    for (char c : a) {
        if (c == '0') countA_0++;
    }
    int countB_0 = 0;
    for (char c : b) {
        if (c == '0') countB_0++;
    }

    if (countA_0 != countB_0) {
        cout << -1 << "\n";
        return;
    }
    
    // 2. 核心技巧：(A + A) 字符串
    string a_doubled = a + a;

    // 3. 在 A' 中查找 B (使用 KMP 替换 std::string::find)
    // 复杂度 O( (2N) + N ) = O(N)
    int pos = kmp_search(a_doubled, b);

    // 4. 输出结果
    cout << pos << "\n";
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