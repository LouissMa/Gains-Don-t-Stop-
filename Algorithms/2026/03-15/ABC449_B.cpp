#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int h,w,q;
    cin>>h>>w>>q;
    while(q --)
    {
        int op;
        cin>>op;
        int x;
        cin>>x;
        if(op == 1)
        {
            cout<<x * w<<endl;
            h -= x;
        }
        else 
        {
            cout<<x * h<<endl;
            w -= x;
        }
    }
    return 0;
}