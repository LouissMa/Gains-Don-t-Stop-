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
    vector<int> a(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    sort(a.begin(),a.end());
    int ans = 1e9;
    for(int i=0;i<=k;i++)
    {
        ans = min(ans,a[i+n-k-1] - a[i]);
    }
    cout<<ans<<endl;
    return 0;
}