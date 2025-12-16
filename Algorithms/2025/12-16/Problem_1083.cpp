#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

int n,m;
int diff[1000011],need[1000011],rest[1000011],r[1000011],l[1000011],d[1000011];

bool check(int mid)
{
    memset(diff,0,sizeof(diff));
    for(int i=1;i<=mid;i++)
    {
        diff[l[i]] += d[i];
        diff[r[i]+1] -= d[i];
    }
    for(int i=1;i<=n;i++)
    {
        need[i] = need[i-1] + diff[i];
        if(need[i] > rest[i]) return 0;
    }
    return 1;
}
signed main()
{
    SPEED;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>rest[i];
    for(int i=1;i<=m;i++) cin>>d[i]>>l[i]>>r[i];
    int be = 1,ed = m;
    if(check(m))
    {
        cout<<0<<endl;
        return 0;
    }
    while(be < ed)
    {
        int mid = (be+ed)/2;
        if(check(mid)) be = mid+1;
        else ed = mid;
    }
    cout<<-1<<endl<<be<<endl;
    return 0;
}