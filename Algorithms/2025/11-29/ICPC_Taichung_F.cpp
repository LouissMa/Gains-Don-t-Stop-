#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e6+10;
int a[N],b[N],c[N];
signed main()
{
    SPEED;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) b[i] = __gcd(b[i-1],a[i]);
    for(int i=n;i>=1;i--) c[i] = __gcd(c[i+1],a[i]);
    int ans = 0;
    for(int i=1;i<n;i++)
    {
        ans += min(b[i],c[i]);
    }
    cout<<ans<<endl;
    return 0;
}