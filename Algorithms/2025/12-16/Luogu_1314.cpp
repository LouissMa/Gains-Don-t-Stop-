#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2e5+10;
int w[N],v[N],l[N],r[N];
int n,m,s;
int cnt[N];
int sumv[N];
int check(int mid)
{
    int sum = 0;
    memset(cnt,0,sizeof cnt);
    memset(sumv,0,sizeof sumv);
    for(int i=1;i<=n;i++)
    {
        cnt[i] = cnt[i-1];
        sumv[i] = sumv[i-1];
        if(w[i] >= mid)
        {
            cnt[i]++;
            sumv[i] += v[i];
        }
    }
    for(int i=1;i<=m;i++)
    {
        sum += (cnt[r[i]] - cnt[l[i]-1]) * (sumv[r[i]] - sumv[l[i]-1]);
    }
    return sum;
}
signed main()
{
    SPEED;
    cin>>n>>m>>s;
    int ans = 1e18;
    int L = 0,R = 0;
    for(int i=1;i<=n;i++) 
    {
        cin>>w[i]>>v[i];
        R = max(R,w[i]);
    }
    for(int i=1;i<=m;i++) cin>>l[i]>>r[i];
    while(L <= R)
    {
        int mid = (L+R) >> 1;
        int y = check(mid);
        ans = min(ans,abs(s - y));
        if(y < s) R = mid - 1;
        else L = mid + 1;
    }
    cout<<ans<<endl;
    return 0;
}