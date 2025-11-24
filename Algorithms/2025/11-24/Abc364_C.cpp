#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,x,y;
    cin>>n>>x>>y;
    int ans = n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    sort(a.begin(),a.end(),greater<int>());
    sort(b.begin(),b.end(),greater<int>());
    for(int i=0;i<n;i++)
    {
        x -= a[i];
        if(x < 0) ans = min(ans,i+1);
    }
    for(int i=0;i<n;i++)
    {
        y -= b[i];
        if(y < 0) ans = min(ans,i+1);
    }
    cout<<ans<<endl;
    return 0;
}