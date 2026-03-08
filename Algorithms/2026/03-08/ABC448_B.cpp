#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1010;
int a[N],b[N],c[N];
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>c[i];
    for(int i1=1;i1<=n;i1++)
    {
        cin>>a[i1]>>b[i1];
    }
    int ans = 0;
    for(int i=1;i<=n;i++)
    {
        int cs = min(c[a[i]],b[i]);
        ans +=cs;
        c[a[i]] -= cs;
    }
    cout<<ans<<"\n";
    return 0;
}