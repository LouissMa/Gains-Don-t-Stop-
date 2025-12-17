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
    vector<int> h(n);
    for(int i=0;i<n;i++) cin>>h[i];
    int ans = 0;
    sort(h.begin(),h.end());
    int l = 0,r = n-1;
    int last = 0;
    while(l <= r)
    {
        if(l == r)
        {
            ans += (h[l] - last) * (h[l] - last);
            break;
        }
        ans += (h[r] - last) * (h[r] - last);
        last = h[r];
        r--;
        ans += (h[l] - last) * (h[l] - last);
        last = h[l];
        l++;
    }
    cout<<ans<<endl;
    return 0;
}