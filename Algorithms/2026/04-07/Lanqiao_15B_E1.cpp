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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    map<int, vector<int>> mp;
    for (auto u : a) {
        for (int i = 1; i <= u / i; i++) {
            if (u % i == 0) { 
                mp[i].push_back(u);
                if (i != u / i) mp[u / i].push_back(u);
            }
        }
    }
    
    // 神级优化：使用 rbegin() 逆序遍历 map，从最大的约数开始找！
    for (auto it = mp.rbegin(); it != mp.rend(); ++it) {
        auto& v = it->second;
        if (v.size() >= 3) {
            // 找到了最大的满足条件的桶！
            sort(v.begin(), v.end());
            // 直接输出前三个，这就是绝对的最优解！
            cout << v[0] << " " << v[1] << " " << v[2] << "\n";
            return; // 立刻下班，后面的根本不需要看了
        }
    }
}
signed main() 
{
    SPEED;
    int t = 1;
    while(t--) 
    {
        solve();
    }
    return 0;
}