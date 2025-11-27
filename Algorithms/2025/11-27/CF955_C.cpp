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

void solve() 
{
    int n, l, r;
    cin >> n >> l >> r;  // Read n first
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    
    int ans = 0;
    vector<int> pre(n + 1);
    for(int i = 0; i < n; i++) pre[i + 1] = pre[i] + a[i];
    
    vector<int> dp(n + 1);
    multiset<int, greater<int>> s;  // Use greater for max element access
    dp[0] = 0;
    
    for(int i = 1, j = 0, k = 0; i <= n; i++)
    {
       dp[i] = dp[i-1];

        while(k < i && pre[i] - pre[k] >= l) 
        {
            s.insert(dp[k]);
            k++;
        }
        
        // Remove invalid left boundaries where sum > r
        while(j < i && pre[i] - pre[j] > r) {
            s.erase(s.find(dp[j]));
            j++;
        }
        
        // Update dp[i] if we have valid ranges
        if(!s.empty()) {
            dp[i] = max(dp[i], *s.begin() + 1);
        }
    }
    cout << dp[n] << endl;
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