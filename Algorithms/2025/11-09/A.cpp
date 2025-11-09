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
    for(int i=0;i<s.size();i++)
    {
        if(s[i] == '.') continue;
        else
        {
            cout<<s[i];
        }
    }
    cout<<endl;
    return 0;
}