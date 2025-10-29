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
    char a = s[0];
    char b = s[1];
    char c = s[2];
    cout<<b<<c<<a<<" ";
    cout<<c<<a<<b<<endl;
    return 0;
}