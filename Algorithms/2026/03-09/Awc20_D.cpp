#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

struct wifi{
    int x,r;
    bool operator < (const wifi &a) const
    {
        return x < a.x;
    }
};
signed main()
{
    SPEED;
    int n,l;
    cin>>n>>l;
    vector<wifi> v;
    for(int i=0;i<n;i++)
    {
        int x,r;
        cin>>x>>r;
        v.push_back({x - r,x + r});
    }  
    sort(v.begin(), v.end());
    bool ok = true;
    if(v[0].x > 0)
    {
        cout<<"No\n";
        return 0;
    }
    int mx = v[0].r;
    for(int i=1;i<n;i++)
    {
        if(v[i].x > mx)
        {
            cout<<"No\n";
            return 0;
        }
        else mx = max(mx,v[i].r);
    }
    if(mx < l) cout<<"No\n";
    else cout<<"Yes\n";
    return 0;
}