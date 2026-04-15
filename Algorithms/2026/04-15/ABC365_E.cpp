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
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    int ans = 0;
    for(int k=0;k<27;k++)
    {
        int cnt = 0;
        int x = 0;
        for(int i=0;i<n;i++)
        {
            x ^= (a[i] >> k & 1);
            cnt += x;
        }
        ans += (1LL << k) * cnt * (n+1-cnt);
    }
    for(int i=0;i<n;i++) ans -= a[i];
    cout<<ans<<endl;
    return 0;
}