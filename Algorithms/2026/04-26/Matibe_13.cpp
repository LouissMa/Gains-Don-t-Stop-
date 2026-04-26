#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin>>n;
    int ans = 1;
    for(int i=n;i>=1;i--)
    {
        ans = (ans * i) % 2026;
    }
    cout<<ans<<endl;
    return 0;   
}