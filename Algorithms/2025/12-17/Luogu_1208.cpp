#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    vector<PII> a(m+1);
    for(int i=1;i<=m;i++)
    {
        cin>>a[i].first>>a[i].second;
    }
    sort(a.begin()+1,a.end());
    int ans = 0,sum = 0;
    for(int i=1;i<=m;i++)
    {
        if(sum <= n)
        {
            int t = 0;
            if(n - sum >= a[i].second)
            {
                ans += a[i].second * a[i].first;
                t = a[i].second;
            }
            else{
                ans += (n - sum) * a[i].first;
                t = n - sum;
            }
            sum += t;
        }
    }
    cout<<ans<<endl;
    return 0;
}