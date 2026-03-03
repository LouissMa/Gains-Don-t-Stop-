#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,k;
    cin>>n>>k;
    int cnt = 0;
    int ans = 0;
    for(int i=1;i<=n;i++)
    {
        int c,d;
        cin>>c>>d;
        if(c <= k)
        {
            cnt ++;
            ans += d;
        }
    }
    cout<<ans<<endl;
    return 0;
}