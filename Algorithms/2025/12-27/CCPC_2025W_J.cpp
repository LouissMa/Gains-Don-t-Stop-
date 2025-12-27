#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    string s;
    while(cin>>s)
    {
        if(s.back() == 'n')
        {
            s += 'g';
        }
        cout<<s<<" ";
    }
    cout<<endl;
    return 0;
}