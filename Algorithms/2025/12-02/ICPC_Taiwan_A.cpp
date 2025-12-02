#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int x,d;
    cin>>x>>d;
    if(2 * x <= d)
    {
        cout<<"double it\n";
    }
    else
    {
        cout<<"take it\n";
    }
    return 0;
}