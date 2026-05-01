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
    int n = s.size();
    s = " " + s;
    bool ok = true;
    if(n % 2 != 0) ok = false;
    for(int i=2;i<=n;i+=2)
    {
        if(s[i] != s[i-1]) ok = false;
    }
    map<char,int> mp;
    for(int i=1;i<=n;i++){
        mp[s[i]]++;
    }
    for(auto i:mp)
    {
        if(i.second != 2) ok = false;
    }
    if(ok) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}