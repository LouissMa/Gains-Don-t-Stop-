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
    vector<string> s(n);
    int maxx = 0;
    string t;
    for(int i=0;i<n;i++)
    {
        cin>>s[i];
        maxx = max(maxx,(int)s[i].size());
        if(s[i].size()==maxx) t = s[i];
    }
    for(int i=0;i<n;i++)
    {
        if(s[i] == t) 
        {
            cout<<s[i]<<"\n";
            continue;
        }
        int d = maxx - s[i].size();
        d = d / 2;
        s[i] = string(d,'.') + s[i] + string(d,'.');
        cout<<s[i]<<"\n";
    }
    return 0;
}