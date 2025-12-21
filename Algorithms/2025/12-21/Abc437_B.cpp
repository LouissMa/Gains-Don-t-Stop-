#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int h,w,n;
    cin>>h>>w>>n;
    vector<vector<int>> g(h+1,vector<int>(w+1));
    vector<int> v(100);
    for(int i=1;i<=h;i++)
    {
        for(int j=1;j<=w;j++) 
        {
            int x;
            cin>>x;
            v[x] = i;
        }
    }
    vector<int> a(n+1,0);
    for(int i=0;i<n;i++)
    {
        int b;
        cin>>b;
        a[v[b]] ++;
    }
    int ans = 0;
    for(auto x : a)
    {
        ans = max(ans,x);
    }
    cout<<ans<<"\n";
    return 0;
}