#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,d,k;
    cin>>n>>d>>k;
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        int w;
        cin>>w;
        w -= d * k;
        if(w >= 1) ans ++;
    }
    cout<<ans<<endl;
    return 0;
}