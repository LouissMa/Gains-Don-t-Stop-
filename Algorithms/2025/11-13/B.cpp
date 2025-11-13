#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    vector<bool> v(n+1);
    for(int i=1;i<=m;i++)
    {
        int a;
        cin>>a;
        char b;
        cin>>b;
        if(b == 'M' && !v[a])
        {
            cout<<"Yes\n";
            v[a] = true;
        }
        else
        {
            cout<<"No\n";
        }
    }
    return 0;
}