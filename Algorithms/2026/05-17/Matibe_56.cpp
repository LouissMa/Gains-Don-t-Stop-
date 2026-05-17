#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    string s;
    cin>>s;
    int ans = 0;
    for(auto i : s)
    {
        ans += (int)i;
    }
    cout<<ans<<endl;
    return 0;
}