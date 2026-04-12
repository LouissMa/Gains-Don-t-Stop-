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
    for(int i=0;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        ans += min(a,b);
    }
    cout<<ans<<endl;
    return 0;
}