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
    vector<int> a(n);
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        if(a[i] == 1) continue;
        else ans ++;
    }
    cout<<ans<<endl;
    return 0;
}