#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n=4;
    vector<int> a(n);
    map<int,int> mp;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        mp[a[i]]++;
    }
    int ans = 0;
    for(auto v : mp)
    {
        if(v.second >= 2) ans += v.second/2;
    }
    cout<<ans<<endl;
    return 0;
}