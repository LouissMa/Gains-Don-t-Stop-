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
        int c,m;
        cin>>c>>m;
        int p = 0;
        for(int j=0;j<m;j++)
        {
            int x;
            cin>>x;
            p += x;
        }
        a[i] = p - c;
    }
    sort(a.begin(), a.end(),greater<int>());
    int ans = 0;
    for(int i=0;i<k;i++)
    {
        if(a[i] > 0) ans += a[i];
    }
    cout<<ans<<endl;
    return 0;
}