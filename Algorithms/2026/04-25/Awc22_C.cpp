#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m,k,T;
    cin>>n>>m>>k>>T;
    set<int> b;
    for(int i=1;i<=m;i++) 
    {
        int x;
        cin>>x;
        b.insert(x);
    }
    vector<int> a(n + 1);
    vector<int> pre(n + 1);
    pre[0] = 0;
    for(int i=1;i<=n;i++)
    {
        if(b.count(i)) a[i] = 1;
        else a[i] = 0;
        pre[i] = pre[i - 1] + a[i];
    }
    for(int i=0;i<k;i++)
    {
        int l,r;
        cin>>l>>r;
        int ans = pre[r] - pre[l - 1];
        if(ans >= T)
        {
            cout<<"YES\n";
        }
        else cout<<"NO\n";
    }
    return 0;
}