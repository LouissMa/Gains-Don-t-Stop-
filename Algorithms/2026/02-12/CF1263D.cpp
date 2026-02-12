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
    vector<int> fa(26,-1);
    vector<bool>st(26);
    auto find = [&](int x){
        while(fa[x] >= 0 && fa[fa[x]] >= 0)
        {
            x = fa[x] = fa[fa[x]];
        }
        return fa[x] >= 0 ? fa[x] : x;
    };
    for(int i=0;i<n;i++)
    {
        string s;
        cin>>s;
        st[s[0] - 'a'] = true;
        for(int j=1;j<s.size();j++)
        {
            int x = find(s[0] - 'a');
            int y = find(s[j] - 'a');
            if(x != y) fa[y] = x;
        }
    }
    int ans = 0;
    for(int i=0;i<26;i++)
    {
        if(st[i] && fa[i] == -1) ans ++;
    }
    cout<<ans<<endl;
    return 0;
}