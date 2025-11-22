#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
const int N = 150010;
struct node
{
    int t1, t2;
    bool operator<(const node &a) const{
        return t2 < a.t2;
    }
}b[N];
signed main()
{
    SPEED;
    int n;
    cin>>n;
    int sum = 0;
    int ans = 0;
    priority_queue<int> q;
    for(int i=1;i<=n;i++) cin>>b[i].t1>>b[i].t2;
    sort(b+1, b+1+n);
    for(int i=1;i<=n;i++)
    {
        sum += b[i].t1;
        q.push(b[i].t1);
        if(sum <= b[i].t2) ans++;
        else
        {
            sum -= q.top();
            q.pop();
        }
    }
    cout<<ans<<"\n";
    return 0;
}