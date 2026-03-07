#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2e5 +10;
struct node{
    int w,d;
    bool operator < (const node &a) const{
        return w + d < a.w + a.d;
    }
}a[N];
signed main()
{
    SPEED;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].w>>a[i].d;
    int ans = 0,sum = 0;
    sort(a + 1, a + n + 1);
    priority_queue<int> q;
    for(int i=1;i<=n;i++)
    {
        sum += a[i].w;
        q.push(a[i].w);
        if(sum <= a[i].d + a[i].w) ans ++;
        else{
            sum -= q.top();
            q.pop();
        }
    }
    cout<<ans<<endl;
    return 0;
}