#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e4 + 10;
int a[N];
signed main()
{
    SPEED;
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i];
    }
    while(q --)
    {
        int op;
        int l,r,x;
        cin>>op;
        int ans = 0;
        if(op == 1)
        {
            cin>>l>>r>>x;
            for(int i=l;i<=r;i++) 
            {
                a[i] += x;
            }
        }
        else if(op == 2)
        {
            cin>>l>>r>>x;
            for(int i=l;i<=r;i++)
            {
                if(a[i] > x) a[i] = x;
            }
        }
        else 
        {
            cin>>l>>r;
            for(int i=l;i<=r;i++) ans += a[i];
            cout<<ans<<endl;
        }
    }
    return 0;
}