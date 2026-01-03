#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

void solve() 
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    // 统计每个字符出现次数
    map<char, int> mp;
    for(int i = 0; i < n; i++) {
        mp[s[i]]++;
    }
    
    // 将出现次数提取到vector中排序
    vector<int> counts;
    for(auto& [ch, cnt] : mp) {
        counts.push_back(cnt);
    }
    sort(counts.begin(), counts.end());
    
    int k = counts.size();  // 不同字符种类数
    
    // 检查是否连续+1
    bool beautiful = true;
    for(int i = 1; i < k; i++) {
        if(counts[i] != counts[i-1] + 1) {
            beautiful = false;
            break;
        }
    }
    
    // 验证总和是否等于n（可选，但连续已经隐含了正确性）
    // 也可以验证：counts[0]应该等于(n - k*(k-1)/2) / k
    
    if(beautiful) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

signed main() 
{
    SPEED;
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}