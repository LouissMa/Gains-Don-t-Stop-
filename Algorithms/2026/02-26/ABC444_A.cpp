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
    string s = to_string(n);
    int len = s.size();
    int now = n % 10;
    bool ok = true;
    for(int i=0;i<len;i++)
    {
        int t = n%10;
        if(t != now)
        {
            ok = false;
            break;
        }
        n/=10;
    }
    if(ok)
    {
        cout<<"Yes\n";
    }
    else
    {
        cout<<"No\n";
    }
    return 0;
}