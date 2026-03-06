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
    vector<int> c(m);
    for(int i=0;i<m;i++) cin>>c[i];
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        map<int,int> mp;
        int k;
        cin>>k;
        for(int j=0;j<k;j++)
        {
            int p;
            cin>>p;
            p --;
            mp[p] ++;
        }
        for(auto [r,p] : mp)
        {
            if(p < c[r]) ans += p;
        }
    }
    cout<<ans<<endl;
    return 0;
}