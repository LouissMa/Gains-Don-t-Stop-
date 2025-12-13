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
    vector<int> l(n),r(n);
    int ans = n * (n-1) / 2;
    for(int i=0;i<n;i++)
    {
        cin>>l[i]>>r[i];
    }
    sort(l.begin(),l.end());
    sort(r.begin(),r.end());
    for(int i=0,j=0;i<n;i++)
    {
        while(j < n && r[j] < l[i]) j++;
        ans -= j;
    }
    cout<<ans<<endl;
    return 0;
}