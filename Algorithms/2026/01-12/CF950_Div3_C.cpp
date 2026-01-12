#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void solve() 
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    
    int m;
    cin >> m;
    vector<int> d(m);
    for(int i = 0; i < m; i++) cin >> d[i];
    
    int ans = 1;
    
    // 最后一次操作必须在 b 里出现过
    if (find(b.begin(), b.end(), d[m-1]) == b.end()) {
        ans = 0;
    }
    
    multiset<int> s(d.begin(), d.end());
    
    for(int i = 0; i < n; i++) 
    {
        if(b[i] != a[i]) 
        {
            if(s.find(b[i]) == s.end())  // 更稳妥的写法
            {
                ans = 0;
                break;
            }
            s.erase(s.find(b[i]));
        }
    }
    
    if(ans) cout << "YES\n";
    else    cout << "NO\n";
}

signed main() 
{
    SPEED;
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}