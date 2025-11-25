#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
signed main()
{
    SPEED;
    int n,t,p;
    cin>>n>>t>>p;
    vector<int> a(n);
    int cnt = 0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        if(a[i] >= t) cnt++;
    }
    int ans= 0;
    if(cnt >= p) ans = 0;
    else
    {
        sort(a.begin(),a.end(),greater<int>());
        ans = t - a[p-1];
    }
    cout<<ans<<endl;
    return 0;
}