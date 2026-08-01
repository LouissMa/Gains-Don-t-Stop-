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
    for(int i=0;i<n;i++)
    {
        if(s[i] =='o') continue;
        if(i - 1 >= 0 && s[i - 1] == 'o') continue;
        if(i + 1 < n&&s[i + 1] == 'o') continue;
        ans ++;
    }
    cout<<ans<<"\n";
    return 0;
}