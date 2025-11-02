
/*
    https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3378
    堆
*/

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
    priority_queue<int,vector<int>,greater<int>> q;
    for(int i=0;i<n;i++)
    {
        int op;
        cin>>op;
        if(op == 1)
        {
            int x;
            cin>>x;
            q.push(x);
        }
        else if(op == 2)
        {
            cout<<q.top()<<endl;
        }
        else
        {
            q.pop();
        }
    }
    return 0;
}