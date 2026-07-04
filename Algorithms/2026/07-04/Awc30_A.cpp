#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        if(a < m)
        {
            cout<<0<<" "<<a<<"\n";
        }
        else
        {
            int t = a / m;
            cout<<t<<" "<<a - t * m<<"\n";
        }
    }
    return 0;
}