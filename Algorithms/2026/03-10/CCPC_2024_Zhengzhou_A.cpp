#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

void solve() 
{
    int n,d;
    cin>>n>>d;
    int l = to_string(n).size();
    int pw = 1;
    for(int i=0;i<l;i++)
    {
        pw *= 10;
    }
    int lo = pw * (1234567890 + d);
    int k = (lo+n-1)/n;
    cout<<k<<endl;
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