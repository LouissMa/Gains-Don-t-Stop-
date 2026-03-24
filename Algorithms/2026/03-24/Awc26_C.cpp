#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5 +10;
int a[N];
signed main()
{
    SPEED;
    int n,t,m;
    cin>>n>>t>>m;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        x *= t;
        a[i] = x;
    }
    sort(a+1,a+1+n);
    int cnt = 0,sum = 0;
    for(int i=1;i<=n;i++)
    {
        if(sum + a[i] <= m)
        {
            sum +=a[i];
            cnt ++;
        }
        else break;
    }
    cout<<cnt<<endl;
    return 0;
}