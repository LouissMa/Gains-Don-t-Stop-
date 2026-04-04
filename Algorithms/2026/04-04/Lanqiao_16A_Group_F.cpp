#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5 +10;
int last[N];

signed main()
{
    SPEED;
    string s;
    cin>>s;
    int n = s.size();
    s = " " + s;
    int tot = 0;
    for(int i=1;i<=n;i++)
    {
        if(s[i] == s[i - 1] || s[i] == s[i - 1] + 1) continue;
        last[ ++ tot] = i - 1;
    }
    last[ ++ tot] = n;
    int ans = 0;
    for(int i=1;i<=tot;i++)
    {
        int l = last[i] - last[i - 1];
        ans += l * (l + 1) / 2;
        if(i == 1) continue;
        int l2 = last[i - 1] - last[i - 2];
        ans += l * l2;
    }
    cout<<ans<<endl;
    return 0;
}