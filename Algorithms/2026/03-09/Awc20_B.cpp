#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m,s;
    cin>>n>>m>>s;
    vector<int> d(n + 1);
    for(int i=1;i<=n;i++) cin>>d[i];
    vector<int> a(n + 1);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        a[x] += y;
    }
    int ans = s;
    int op = 0;
    for(int i=1;i<=n;i++)
    {
        ans -= d[i];
        if(op)
        {
            ans -= d[i];
        }
        if(ans <= 0) op = 1;
        ans += a[i];
    }
    cout<<ans<<endl;
    return 0;
}