#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    string s,t;
    cin>>s>>t;
    if(s == t)
    {
        cout<<0<<endl;
        return 0;
    }
    int n = s.size();
    int m = t.size();
    for(int i=0;i<min(n,m);i++)
    {
        if(s[i] != t[i])
        {
            cout<<i+1<<endl;
            return 0;
        }
    }
    cout<<min(n,m)+1<<endl;
    return 0;
}