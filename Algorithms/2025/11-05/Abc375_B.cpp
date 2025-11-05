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
    vector<int> X(n+1), Y(n+1);
    for(int i=1;i<=n;i++) cin>>X[i]>>Y[i];
    double ans = 0;
    for(int i=0;i<=n;i++)
    {
        int j = i == n ? 0 : i+1;
        ans += hypot(X[i]-X[j], Y[i]-Y[j]);
    }
    cout<<fixed<<setprecision(10)<<ans<<endl;
    return 0;
}