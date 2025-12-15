#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

int n,m,k;
int a[50005];
bool check(int mid)
{
    int ans = 0;
    int st = 0;
    for(int i=1;i<=n + 1;i++)
    {
        if(a[i] - st < mid)
        {
            ans = ans + 1;
        }
        else st = a[i];
    }
    return ans <= m;
}
signed main()
{
    SPEED;
    cin>>k>>n>>m;
    for(int i=1;i<=n;++i) cin>>a[i];
    a[n+1] = k;
    int l = 0, r = k, mid;
    while(l < r)
    {
        mid = (l + r + 1) >> 1;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }
    cout<<l<<endl;
    return 0;
}