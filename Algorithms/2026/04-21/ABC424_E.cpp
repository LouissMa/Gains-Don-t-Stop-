#include <bits/stdc++.h>
using namespace std;
#define int long long // 由于K和A_i很大，使用long long防止溢出
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

// check函数: 判断是否能得到至少 X 根长度不小于 m 的木棍
// K 在这里的版本中被简化，假设K足够大，只判断理论上的可能性
// 这是一个有效的简化，因为切割最长的木棍总是最优的策略
bool check(int m, int x, const vector<int>& a) {
    if (m == 0) return true; // 长度为0的木棍可以认为是无限多的
    long long count = 0;
    for (int val : a) {
        count += val / m;
    }
    return count >= x;
}

void solve() 
{
    int n, k, x;
    cin >> n >> k >> x;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // 使用二分答案来查找满足条件的最大的 m
    int lo = 0, hi = 2e9, ans = 0; // hi可以设置为A_i的最大值

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (mid == 0) { // mid为0时没有意义，直接跳过
            lo = mid + 1;
            continue;
        }

        // 检查长度 mid 是否可行
        long long count = 0;
        for (int val : a) {
            count += val / mid;
        }

        if (count >= x) {
            // 如果能凑够x根，说明mid是一个可能的答案
            // 我们尝试寻找更大的答案
            ans = mid;
            lo = mid + 1;
        } else {
            // 如果凑不够x根，说明mid太大了，需要减小
            hi = mid - 1;
        }
    }
    cout << ans << endl;
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