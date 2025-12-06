#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    int res;
    int fa = 1 + a[1] - 1;
    for(int i=2;i<=min(n,fa);i++)
    {
        if(a[i] + i - 1 > fa) fa = a[i] + i - 1;
    }
    res = min(fa,n);
    cout<<res<<endl;
    return 0;
}