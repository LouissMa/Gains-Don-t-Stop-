#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,x;
    cin>>n>>x;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        if(a < x)
        {
            x = a;
            cout<<1<<"\n";
        }
        else cout<<0<<"\n";
    }
    return 0;
}