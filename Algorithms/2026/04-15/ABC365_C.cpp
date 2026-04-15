#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    vector<int> a(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    int l = 0,r = 1e9+1;
    while(l < r)
    {
        int mid = (l+r + 1) >> 1;
        int sum = 0;
        for(int i=0;i<n;i++) sum += min(mid,a[i]);
        if(sum <= m) l = mid;
        else r = mid - 1;
    }
    if(l > 1e9)
    {
        cout << "infinite\n";
    }
    else cout<<l<<"\n";
    return 0;
}