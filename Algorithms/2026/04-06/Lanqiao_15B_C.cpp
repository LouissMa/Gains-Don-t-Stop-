#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

bool check(int x) //判断x是否为好数
{
    int tmp=0;
    while(x)
    {
        int now=x%10;
        x/=10;
        tmp++;
        if(tmp%2!=now%2) return 0;
    }
    return 1;
}

signed main()
{
    SPEED;
    int n;
    cin>>n;
    int ans = 0;
    for(int i =1;i<=n;i++)
    {
        if(check(i)) ans ++;
    }
    cout<<ans<<endl;
    return 0;
}