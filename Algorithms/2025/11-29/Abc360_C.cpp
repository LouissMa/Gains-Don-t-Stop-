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
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        a[i]--;
    }
    vector<int> w(n);
    int ans = 0;
    vector<int> f(n);
    for(int i=0;i<n;i++)
    {
        cin>>w[i];
        f[a[i]] = max(f[a[i]], w[i]);
        ans += w[i];
    }
    ans -= accumulate(f.begin(), f.end(), 0);
    cout<<ans<<endl;
    return 0;
}