#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int x;
    cin>>x;
    int n;
    cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    int q;
    cin>>q;
    int ans = x;
    vector<bool> vis(n+1, false); 
    while(q--)
    {
        int p;
        cin>>p;
        if(vis[p])
        {
            ans -= a[p];
            cout<<ans<<"\n";
            vis[p] = false;
        }
        else
        {
            ans += a[p];
            cout<<ans<<"\n";
            vis[p] = true;
        }
    }
    return 0;
}