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
    vector<string> s(n);
    for(int i=0;i<n;i++) cin>>s[i];
    vector<int> vis(n);
    int ans = 1e18;
    for(int i=0;i<(1<<n);i++)
    {
        int c = 0;
        for(int j=0;j<m;j++) vis[j] = 0;
        for(int j=0;j<n;j++)
        {
            if(i>>j&1 ^ 1) continue;
            c++;
            for(int t = 0;t<m;t++)
            {
                if(s[j][t] == 'o') vis[t] = 1;
            }
        }
        int flag = 0;
        for(int j=0;j<m;j++)
        {
            if(!vis[j]) flag = 1;
        }
        if(!flag) ans = min(ans,c);
    }
    cout<<ans<<endl;
    return 0;
}