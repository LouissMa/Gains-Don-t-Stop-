/*
Problem: CirnoNine (Easy Version)
Strategy: Enumerate all "Good Numbers" and calculate min operations greedily.
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);

void solve() 
{
    int x;
    cin >> x;
    
    // 初始化为一个较大的值
    int ans = 2e18; 
    
    // 枚举所有可能的目标“好数字” g
    // x <= 10^6，通常目标不会超过 10^14，枚举到 18 位足以覆盖所有情况
    int g = 0;
    for(int len = 1; len <= 18; len++) {
        g = g * 10 + 9;
        
        // 策略 1: 只使用加法 (+9)
        // 要求: g >= x 且 差值是 9 的倍数
        if (g >= x && (g - x) % 9 == 0) {
            ans = min(ans, (g - x) / 9);
        }
        
        // 策略 2: 使用一次乘法 (x9)
        // 过程: x -> 加 k1 次 9 -> 乘 9 -> 加 k2 次 9 -> g
        // 推导: 9 * (x + 9*k1) + 9*k2 = g
        //      => x + 9*k1 + k2 = g / 9
        //      => 9*k1 + k2 = (g / 9) - x
        // 令 C = (g / 9) - x。我们需要 g >= 9*x 保证 C >= 0。
        // 总步数 = k1 + 1 + k2
        //        = k1 + 1 + (C - 9*k1) 
        //        = C + 1 - 8*k1
        // 要使步数最小，k1 应取最大值。由 k2 >= 0 得 9*k1 <= C，故 k1_max = C / 9。
        
        if (g >= 9 * x) {
            int C = (g / 9) - x;
            int k1 = C / 9;
            int k2 = C % 9;
            int ops = k1 + 1 + k2;
            ans = min(ans, ops);
        }
    }
    
    cout << ans << endl;
}

signed main() 
{
    SPEED;
    int t;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}