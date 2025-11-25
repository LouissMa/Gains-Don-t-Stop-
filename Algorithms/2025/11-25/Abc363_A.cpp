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
    if(n <= 99)
    {
        ans = 100 - n;
    }
    else if(n <= 199) ans = 200 - n;
    else ans = 300 - n;
    cout<<ans<<endl;
    return 0;
}