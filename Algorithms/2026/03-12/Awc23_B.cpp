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
    int ans = 0;
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        ans += a;
        ans -= b;
        ans = max(ans,0LL);
    }
    int a;
    cin>>a;
    ans += a;
    cout<<ans<<endl;
    return 0;
}