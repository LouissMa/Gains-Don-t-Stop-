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
    vector<PII> a(n);
    for(int i=0;i<n;i++)
    {
        int p,t;
        cin>>p>>t;
        a[i]={p,t};
    }
    for(int i=0;i<m;i++)
    {
        int k;
        cin>>k;
        int ans0 = 1e10,ans1 = 1e10;
        for(int i=0;i<k;i++)
        {
            int s;
            cin>>s;
            s --;
            if(a[s].second == 0)
            {
                ans0 = min(ans0,a[s].first);
            }
            if(a[s].second == 1) ans1 = min(ans1,a[s].first);
        }
        if(ans0 ==  1e10 || ans1 == 1e10)
        {
            cout<<"-1\n";
        }
        else cout<<ans0 + ans1<<"\n";
    }
    return 0;
}