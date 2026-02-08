#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int x;
    cin>>x;
    bool ok = false;
    for(int i=1;i<x;i++)
    {
        if(i * (i + 1) == x)
        {
            ok = true;
            break;
        }
    }
    if(ok) cout<<"YES\n";
    else cout<<"NO\n";
    return 0;
}