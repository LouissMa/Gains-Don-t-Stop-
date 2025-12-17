#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5+10;
int n,k,a[N];
int l,r,ans1 = -1,ans2 = -1;

int check(int mid)
{
    int sum = 0,ans = 0;
    for(int i=1;i<=n;i++)
    {
        sum = max(sum + a[i],0LL);
        if(sum >= mid)
        {
            sum = 0;
            ans ++;
        }
    }
    return ans;
}
signed main()
{
    SPEED;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    l = 1,r = 1e18;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        if(check(mid) <= k)
        {
            r = mid - 1;
            if(check(mid) == k) ans1 = mid;
        }
        else l = mid + 1;
    }
    l = 1, r = 1e18;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        if(check(mid) >= k)
        {
            l = mid + 1;
            if(check(mid) == k) ans2 = mid;
        }
        else r = mid - 1;
    }
    cout<<ans1<<" "<<ans2<<endl;
    return 0;
}