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
    for(int i=0;i<n;i++) cin>>a[i];
    int ans = 1;
    sort(a.begin(), a.end());
    for(int i=1;i<n;i++)
    {
        if(a[i] != a[i-1] + 1) ans ++;
    }
    cout<<ans<<endl;
    return 0;
}