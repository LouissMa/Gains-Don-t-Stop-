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
    priority_queue<int,vector<int>,greater<int>> p;
    while(q --)
    {
        int op,h;
        cin>>op>>h;
        if(op == 1)
        {
            p.push(h);
        }
        else
        {
            while(!p.empty() && p.top() <= h) p.pop();
        }
        cout<<p.size()<<endl;
    }
    return 0;
}