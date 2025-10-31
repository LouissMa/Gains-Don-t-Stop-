#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 110;
struct days
{
    int q,r;
}a[N];
signed main()
{
    SPEED;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].q>>a[i].r;
    }
    int q;
    cin>>q;
    while(q--)
    {
        int t,d;
        cin>>t>>d;
        int day;
        if(d <= a[t].r) day = a[t].r;
        else
        {
            for(int x = 0;;x++)
            {
                if(a[t].q * x + a[t].r >= d)
                {
                    day = a[t].q * x + a[t].r;
                    break;
                }
            }
        }
        cout<<day<<endl;
    }
    return 0;
}