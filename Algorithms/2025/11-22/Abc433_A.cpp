#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int x,y,z;
    cin>>x>>y>>z;
    if ((x - z * y) % (z - 1) == 0 && (x - z * y) / (z - 1) >= 0) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    return 0;
}