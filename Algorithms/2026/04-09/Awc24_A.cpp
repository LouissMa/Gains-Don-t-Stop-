#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,q;
    cin>>n>>q;
    vector<int> a(n + 1);
    for(int i=1;i<=n;i++) cin>>a[i];
    while(q --)
    {
        int u,v;
        cin>>u>>v;
        if(a[u] <= a[v] || u == v) cout<<"No\n";
        else cout<<"Yes\n";
    }
    return 0;
}