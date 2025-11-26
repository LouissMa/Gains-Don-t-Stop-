#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int xa,ya,xb,yb,xc,yc;
    cin>>xa>>ya>>xb>>yb>>xc>>yc;
    int len1 = (xa-xb)*(xa-xb)+(ya-yb)*(ya-yb);
    int len2 = (xa-xc)*(xa-xc)+(ya-yc)*(ya-yc);
    int len3 = (xb-xc)*(xb-xc)+(yb-yc)*(yb-yc);
    if(len1 + len2 == len3 || len1 + len3 == len2 || len2 + len3 == len1)
    {
        cout<<"Yes\n";
    }
    else
    {
        cout<<"No\n";
    }
    return 0;
}