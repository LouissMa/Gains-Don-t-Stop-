#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,q,s;
    cin>>n>>q>>s;   
    vector<int> a(n + 1);
    for(int i=1;i<=n;i++) cin>>a[i];
    vector<int> pre(n + 1);
    pre[1] = s;
    for(int i=2;i<=n;i++)
    {
        pre[i] = pre[i - 1] + a[i - 1];
    }
    while(q --)
    {
        int x,y;
        cin>>x>>y;
        cout<<pre[x] + y - 1<<"\n";
    }
    return 0;
}