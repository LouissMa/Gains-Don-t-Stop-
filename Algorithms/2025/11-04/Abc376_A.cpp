#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,c;
    cin>>n>>c;
    int pre = 0;
    int ans = 0;
    for(int i=1;i<=n;i++)
    {
        int t;
        cin>>t;
        if(i == 1)
        {
            ans ++;
            pre = t;
            continue;
        }
        if(t - pre >= c)
        {
            ans ++;
            pre = t;
        }
        else continue;
    }
    cout<<ans<<endl;
    return 0;
}