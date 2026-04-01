#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

void solve() 
{
    int n,k;
    cin>>n>>k;
    if(k == 0)
    {
        cout<<0<<endl;
        return;
    }
    if(n >= k)
    {
        cout<<1<<endl;
        return;
    }
    int ans = 1;
    k -= n;
    int i=0,j=1;
    while(k > 0)
    {
        j++;
        if((j&1) == 0) i++;
        ans++;
        k -= (n-i);
    }
    cout<<ans<<endl;
}

signed main() 
{
    SPEED;
    int t = 1;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}