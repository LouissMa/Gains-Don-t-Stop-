#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,t;
    cin>>n>>t;
    vector<int> r(n),c(n);
    int d1 = 0,d2 = 0;
    for(int i=1;i<=t;i++)
    {
        int a;
        cin>>a;
        a--;
        int x = a / n;
        int y = a % n;
        r[x]++;
        c[y]++;
        if(x == y) d1++;
        if(x + y == n-1) d2++;
        if(r[x] == n || c[y] == n || d1 == n || d2 == n)
        {
            cout<<i<<"\n";
            return 0;
        }
    }
    cout<<-1<<"\n";
    return 0;
}