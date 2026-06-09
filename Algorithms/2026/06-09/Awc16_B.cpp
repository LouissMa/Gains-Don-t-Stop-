#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,t;
    cin>>n>>t;
    int ans = 0;
    for(int _ = 1;_ <= n; _ ++)
    {
        int a,c;
        cin>>a>>c;
        if(a >= t) continue;
        ans += (t - a) * c;
    }
    cout<<ans<<endl;
    return 0;
}