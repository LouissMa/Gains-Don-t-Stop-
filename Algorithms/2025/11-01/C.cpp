#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);

signed main()
{
    SPEED;
    int n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;
    vector<int> suma(n + 1, 0), sumb(n + 1, 0);
    for(int i = 0; i < n; i++) {
        suma[i + 1] = suma[i] + (s[i] == 'a' ? 1 : 0);
        sumb[i + 1] = sumb[i] + (s[i] == 'b' ? 1 : 0);
    }
    
    int ans = 0;
    int r1 = 0, r2 = -1;
    
    for(int l = 0; l < n; l++) {
        // 找 r1: 第一个使得 [l, r1] 中 a 的数量 >= a
        r1 = max(r1, l);
        while(r1 < n && suma[r1 + 1] - suma[l] < a) {
            r1++;
        }
        
        if(r1 >= n) break;
        
        // 检查 [l, r1] 的 b 数量
        if(sumb[r1 + 1] - sumb[l] >= b) continue;
        
        r2 = max(r2, r1);
        while(r2 + 1 < n && sumb[r2 + 2] - sumb[l] < b) {
            r2++;
        }
        
        // [r1, r2] 都满足条件
        ans += (r2 - r1 + 1);
    }
    
    cout << ans << endl;
    
    return 0;
}