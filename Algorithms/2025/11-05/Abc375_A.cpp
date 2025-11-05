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
    string s;
    cin>>s;
    int ans = 0;
    s = " " + s;
    for(int i=1;i<=n-2;i++)
    {
        if(s[i] == '#')
        {
            if(s[i+1] == '.' && s[i+2] == '#') ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}