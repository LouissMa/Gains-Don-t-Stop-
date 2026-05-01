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
    string s;
    cin>>s;
    s = " " + s;
    bool ok = true;
    if(n % 2 == 0)
    {
        ok = false;
    }
    if(s[(n+1)/2] != '/') ok = false;
    for(int i=1;i<=(n+1)/2-1;i++)
    {
        if(s[i] != '1') ok = false;
    }
    for(int i=(n+1)/2+1;i<=n;i++)
    {
        if(s[i] != '2') ok = false;
    }
    if(!ok)
    {
        cout<<"No\n";
    }
    else
    {
        cout<<"Yes\n";
    }
    return 0;
}