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
    vector<int> a(n+1),sum(n+1);
    int ans =1e18;
    sum[0] = 0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum[i] = sum[i-1]+a[i];
    }
    multiset<int> s;
    for(int l=1;l<=n;l++)
    {
        for(int r = l + 1;r<=n;r++)
        {
            s.insert(sum[r]-sum[l]);
        }
    }
    for(int r=1;r<n;r++)
    {
        for(int l=0;l<r;l++)
        {
            int val = sum[r]-sum[l];
            auto it = s.lower_bound(val);
            if(it != s.end())
            {
                ans = min(ans,abs(*it - val));
            }
            if(it != s.begin())
            {
                it --;
                ans = min(ans,abs(*it - val));
            }
        }
        for(int r2 = r + 1;r2<=n;r2++)
        {
            s.erase(s.find(sum[r2]-sum[r]));
        }
    }
    cout<<ans<<endl;
    return 0;
}