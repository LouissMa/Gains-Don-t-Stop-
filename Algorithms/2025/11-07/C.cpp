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
    sort(a.begin(), a.end());
    int ans = 0; 
    int suma = 0, sumb = 0;
    int tot = accumulate(a.begin(), a.end(), 0LL);
    ans = tot;
    vector<int> sum(1 << n);
    for(int s=0;s<(1 << n);s++)
    {
        if(s > 0)
        {
            int u = __builtin_ctz(s);
            sum[s] = a[u] + sum[s ^ (1 << u)];
        }
        ans = min(ans,max(sum[s],tot - sum[s]));
    }
    cout<<ans<<endl;
    return 0;
}