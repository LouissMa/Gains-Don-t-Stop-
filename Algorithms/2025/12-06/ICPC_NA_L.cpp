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
    int res = 0;
    int a = 0,b = 0,c = 0;
    while(n--)
    {
        int x,y;
        cin>>x>>y;
        int da = max(0LL,x - a);
        int db = max(0LL,y - b);
        a += da;
        b += db;
        int aa = min(da,c);
        c -= aa;
        da -= aa;
        int bb = min(db,c);
        c -= bb;
        db -= bb;
        res += da + db;
        ++c;
    }
    cout<<res<<endl;
    return 0;
}