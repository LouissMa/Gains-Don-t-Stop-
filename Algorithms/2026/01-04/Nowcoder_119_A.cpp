#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    vector<int> a(5),b(5);
    int sum1 = 0,sum2 = 0;
    for(int i=0;i<5;i++)
    {
        cin>>a[i];
        sum1 += a[i];
    }
    for(int i=0;i<5;i++)
    {
        cin>>b[i];
        sum2 += b[i];
    }
    int maxx = 0,minn = 1e18;
    for(int i=0;i<5;i++)
    {
        sum1 -= a[i];
        int ne = 2 * a[i];
        int cur = sum1 + ne;
        maxx = max(maxx,cur);
        sum1 += a[i];
    }
    for(int i=0;i<5;i++)
    {
        sum2 -= b[i];
        int ne = 2 * b[i];
        int cur = sum2 + ne;
        minn = min(minn,cur);
        sum2 += b[i];
    }
    if(maxx > minn) cout<<"YES\n";
    else cout<<"NO\n";
    return 0;
}