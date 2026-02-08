#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);

signed main()
{
    SPEED;
    int xa, ya, xb, yb;
    cin >> xa >> ya >> xb >> yb;
    if(ya == yb)
    {
        if(abs(xa * yb - xb * ya) == 4) cout<<0<<"\n";
        else cout<<"no answer\n";
        return 0;
    }
    double l = 1.0 * (0 - ya) * (xb - xa) / (yb - ya) + xa;
    double r = 1e18;
    double ans = -1;

    auto check = [&](double mid) -> bool{
        return abs(xa * yb - xb * ya - mid * yb + mid * ya) >= 4;
    };

    while(r - l >= 1e-8)
    {
        double mid = (l + r) / 2;
        if(check(mid))
        {
            ans = mid;
            r = mid;
        }
        else l = mid;
    } 
    if(ans == -1) cout<<"no answer\n";
    else cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}