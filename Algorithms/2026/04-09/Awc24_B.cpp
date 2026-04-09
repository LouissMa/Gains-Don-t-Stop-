#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m,k;
    cin>>n>>m>>k;
    vector<bool> a(n + 1);
    for(int i=1;i<=k;i++) a[i] = true;
    while(m --)
    {
        int x,y;
        cin>>x>>y;
        if(a[x] == false && a[y] == false) continue;
        a[x] = a[y] = true;
    }
    int ans = 0;
    for(int i=1;i<=n;i++) 
    {
        if(a[i]) ans ++;
    }
    cout<<ans<<endl;
    return 0;

}