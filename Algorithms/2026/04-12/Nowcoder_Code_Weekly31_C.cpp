#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    
    int n;
    cin>>n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int ans = 0;  
    int rem = 0;
    for(int i = n; i >= 1; i--) {
        int cost = n - i + 1;
        int av = rem + a[i];
        int tem = av / cost;
        tem = min(tem, a[i]);
        ans += tem;
        rem = av - cost * tem;
    }
    
    cout << ans << "\n";
    
    return 0;
}