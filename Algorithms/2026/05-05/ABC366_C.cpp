#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int q;
    cin>>q;
    map<int,int> mp;
    while(q--)
    {
        int op;
        cin>>op;
        if(op == 1)
        {
            int x;
            cin>>x;
            mp[x] ++;
        }
        else if(op == 2)
        {
            int x;
            cin>>x;
            if(--mp[x] == 0)
            {
                mp.erase(x);
            }
        }
        else
        {
            cout<<mp.size()<<endl;
        }
    }
    return 0;
}