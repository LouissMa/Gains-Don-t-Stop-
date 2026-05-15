#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int mod = 10007;

signed main()
{
    SPEED;
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    // 寻找连续摊位集合的左右边界
    int min_x = 2e18; // 极大值
    int max_x = -2e18; // 极小值
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        min_x = min(min_x, x);
        max_x = max(max_x, x);
    }
    
    int ans = 0; // 记录总分
    
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        
        // 求两个区间的交集 [min_x, max_x] 和 [l, r]
        int L = max(min_x, l);
        int R = min(max_x, r);
        
        int inside = 0;
        // 如果 L <= R，说明两个区间有交集
        if (L <= R) {
            inside = R - L + 1;
        }
        
        // 落在区间外面的点数，每个点加1分，等于本次事件产生的总分增量
        int outside = n - inside;
        
        // 累加并取模
        ans = (ans + outside) % mod;
    }
    
    cout << ans << "\n";
    
    return 0;
}