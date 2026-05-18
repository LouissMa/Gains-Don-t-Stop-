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
    int minn_x = 1e18,maxx_x = 0;
    int minn_y = 1e18,maxx_y = 0;
    for(int i=0;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        minn_x = min(minn_x,x);
        maxx_x = max(maxx_x,x);
        minn_y = min(minn_y,y);
        maxx_y = max(maxx_y,y);
    }
    cout<<(maxx_x-minn_x) * (maxx_y-minn_y)<<endl;
    return 0;
}