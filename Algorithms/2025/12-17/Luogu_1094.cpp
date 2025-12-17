#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int w,n;
    cin>>w>>n;
    vector<int> p(n+1);
    for(int i=1;i<=n;i++) cin>>p[i];
    sort(p.begin()+1,p.end());
    int ans = 0;
    int l=1,r = n;
    while(l <= r)
    {
        if(l < r && p[l] + p[r] <= w)
        {
            ans ++;
            l++;
            r--;
        }
        else
        {
            ans ++;
            r--;
        }
    }
    cout<<ans<<endl;
    return 0;
}