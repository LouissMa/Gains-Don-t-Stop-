#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,x,y,z;
    cin>>n>>x>>y>>z;
    map<int,int> diff;
    for(int i=0;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        diff[a] += (y - x);
        diff[b] += (z - y);
    }
    int cur = n * x;
    int maxx = cur;
    for(auto const& [tem,change]:diff)
    {
        cur += change;
        maxx = max(maxx,cur);
    }
    cout<<maxx<<'\n';
    return 0;
}