#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
const int N = 1e6+10;
int n;
int a[N],sum[N];
int f[7],l[7];
signed main()
{
    SPEED;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>sum[i];
        sum[i] = (sum[i] + sum[i-1]) % 7;
    }
    for(int i=n;i>=1;i--)
    {
        f[sum[i]] = i;
    }
    f[0] = 0;
    for(int i=1;i<=n;i++)
    {
        l[sum[i]] = i;
    }
    int ans = 0;
    for(int i=0;i<6;i++)
    {
        ans = max(ans,l[i]-f[i]);
    }
    cout<<ans<<endl;
    return 0;
}