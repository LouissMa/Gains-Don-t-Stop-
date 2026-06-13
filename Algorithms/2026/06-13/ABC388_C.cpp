#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e6+10;
int a[N];
signed main()
{
    SPEED;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int ans = 0;
    for(int i=1;i<=n;i++)
    {
        int x = a[i] * 2;
        int pos = lower_bound(a+1,a+n+1,x) - a;
        ans += n - pos + 1;
    }
    cout<<ans<<endl;
    return 0;
}