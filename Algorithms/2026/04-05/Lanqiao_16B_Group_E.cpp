#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5 +10;
int a[N],d[N];
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i];
        a[i] *= a[i];
    }
    sort(a + 1, a + n + 1);
    int ans = 1e18;
    for(int i=1;i + m - 1 <= n;i++)
    {
        ans = min(ans,a[i + m - 1] - a[i]);
    }
    cout<<ans<<endl;
    return 0;
}