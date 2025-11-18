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
    while(s.back() == '0') s.pop_back();
    if(s.back() == '.') s.pop_back();
    cout<<s<<"\n";
    return 0;
}