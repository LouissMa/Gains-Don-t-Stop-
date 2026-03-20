#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,q;
    cin>>n>>q;
    vector<int> v(n);
    for(int i=0;i<n;i++) cin>>v[i];
    while(q --)
    {
        int op;
        cin>>op;
        if(op == 1)
        {
            int a,b;
            cin>>a>>b;
            a --;b --;
            v[b] += v[a];
            v[a] = 0;
        }
        else
        {
            int c;
            cin>>c;
            c --;
            cout<<v[c]<<endl;
        }
    }
    return 0;
}