#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,k;
    cin >> n >> k;
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        string s;
        cin>>s;
        int cnt = 0;
        cnt += count(s.begin(), s.end(), '!');
        if(cnt >= k) ans ++;
    }
    cout << ans << endl;
    return 0;
}