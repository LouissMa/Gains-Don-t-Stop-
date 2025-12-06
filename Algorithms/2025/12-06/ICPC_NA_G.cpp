#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
#define ld long double
signed main()
{
    SPEED;
    int n,a,b;
    cin>>n>>a>>b;
    ld ans=  1.0;
    for(int i=1;i<=n;i++)
    {
        int l,r;
        cin>>l>>r;
        if(l > b || r < a) ans = 0;
        else
        {
            l = max(l,a);
            r = min(r,b);
            ans *= 1.0L * (r-l) / (b-a);
        }
    }
    cout<<fixed<<setprecision(6)<<1.0 - ans<<endl;
    return 0;
}