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
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<int> pre(n+1);
    map<int,int> cnt;
    int ans=  0;
    pre[0] = 0;
    for(int i=0;i<n;i++)
    {
        pre[i+1] = pre[i] + a[i];
    }
    int L = pre[n];
    for(int i=0;i<n;i++)
    {
        ans += cnt[(pre[i] - L % m + m) % m];
        ans += cnt[pre[i] % m]++;
    }
    cout<<ans<<endl;
    return 0;
}