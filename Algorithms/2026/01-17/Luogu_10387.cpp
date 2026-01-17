#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5+10;

struct Node
{
    int cost,num;
    bool operator < (const Node &t) const{
        return num < t.num;
    }
}a[N];
signed main()
{
    SPEED;
    int n,s;
    cin>>n>>s;
    int tot = 0,ans = 0;
    int used = 0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i].cost>>a[i].num;
        tot += a[i].cost;
    }
    sort(a,a+n);
    for(int i=0;i<n;i++)
    {
        if(tot >= s)
        {
            ans += (a[i].num - used) * s;
            used += a[i].num - used;
            tot -= a[i].cost;
        }
        else 
        {
            ans += (a[i].num - used) * a[i].cost;
            tot -= a[i].cost;
        }
    }
    cout<<ans<<endl;
    return 0;
}