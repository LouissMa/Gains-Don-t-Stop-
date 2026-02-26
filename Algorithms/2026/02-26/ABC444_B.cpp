#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

int check(int x)
{
    int ans = 0;
    while(x > 0)
    {
        ans += x % 10;
        x /= 10;
    }
    return ans;
}
signed main()
{
    SPEED;
    int n,k;
    cin>>n>>k;
    int cnt = 0;
    for(int i=1;i<=n;i++)
    {
        if(check(i) == k) cnt ++;
    }
    cout<<cnt<<endl;
    return 0;
}