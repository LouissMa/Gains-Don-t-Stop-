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
    vector<int> a(n + 1),b(n + 1);
    for(int i=1;i<=n;i++) cin>>a[i];
    bool ok = true;
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
    }
    for(int i=1;i<=n;i++)
    {
        if(i != b[a[i]])
        {
            ok = false;
            break;
        }
    }
    if(ok) cout<<"Yes\n";
    else cout<<"No\n";
    return 0;
}