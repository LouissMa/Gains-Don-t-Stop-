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
    int pos[26];
    for(int i=0;i<26;i++)
    {
        pos[s[i] - 'A'] = i;
    }
    for(int i=1;i<26;i++)
    {
        ans += abs(pos[i] - pos[i-1]);
    }
    cout<<ans<<endl;
    return 0;
}