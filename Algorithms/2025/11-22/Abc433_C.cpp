#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    string s;
    cin >> s;
    int n = s.size();
    vector<PII> a;
    for(int i = 0; i < n; ) {
        int j = i;
        while(j < n && s[j] == s[i]) {
            j++;
        }
        a.push_back({s[i] - '0', j - i});
        i = j;
    }
    
    int ans = 0;
    for(int i = 0; i + 1 < a.size(); i++) {
        if(a[i].first + 1 == a[i+1].first) {
            ans += min(a[i].second, a[i+1].second);
        }
    }
    
    cout << ans << endl;
    
    return 0;
}