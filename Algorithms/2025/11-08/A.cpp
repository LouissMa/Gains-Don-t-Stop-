#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    vector<string> s(12);
    int ans = 0;
    for(int i=0;i<12;i++)
    {
        cin>>s[i];
        if(i+1 == s[i].size())
        {
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}