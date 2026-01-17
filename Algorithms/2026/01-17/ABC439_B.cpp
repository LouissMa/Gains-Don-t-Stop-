#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

int f(int x)
{
    int s = 0;
    while(x > 0)
    {
        s += (x % 10) * (x % 10);
        x /= 10;
    }
    return s;
}
signed main()
{
    SPEED;
    int n;
    cin>>n;
    for(int i=0;i<1000;i++)
    {
        n = f(n);
    }
    if(n == 1) cout<<"Yes\n";
    else cout<<"No\n";
    return 0;
}