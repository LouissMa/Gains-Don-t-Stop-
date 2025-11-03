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
    map<char,int> mp;
    for(auto c : s)
    {
        mp[c]++;
    }
    if(mp.size() == 3 && mp['A'] == 1 && mp['B'] == 1 && mp['C'] == 1)
    {
        cout<<"Yes\n";
    }
    else
    {
        cout<<"No\n";
    }
    return 0;
}