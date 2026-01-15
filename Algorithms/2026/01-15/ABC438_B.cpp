#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    string s,t;
    cin>>s>>t;
    int ans = 1e18;
    for(int i=0;i+m <= n;i++)
    {
        int cnt = 0;
        for(int j=0;j<m;j++)
        {
            int x = t[j] - '0';
            int y = s[i+j] - '0';
            cnt += (y + 10 - x) % 10;
        }
        ans =  min(ans, cnt);
    }
    cout<<ans<<endl;
    return 0;
}