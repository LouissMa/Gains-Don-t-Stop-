#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

int cnt[26];
signed main()
{
    SPEED;
    int n,l,r;
    cin>>n>>l>>r;
    string s;
    cin>>s;
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        if(i - l >= 0) cnt[s[i - l] - 'a'] ++;
        if(i - r - 1 >= 0) cnt[s[i - r - 1] - 'a'] --;
        ans += cnt[s[i] - 'a'];
    }
    cout<<ans<<endl;
    return 0;
}