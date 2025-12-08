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
    vector<int> a(n),b(m);
    priority_queue<int,vector<int>,greater<int>> p;
    int ans =0;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<m;i++) cin>>b[i];
    sort(a.begin(),a.end(),greater<int>());
    sort(b.begin(),b.end(),greater<int>());
    int j=0;
    for(int i=0;i<m;i++)
    {
        for(;j<n && a[j] >= b[i];j++) p.push(a[j]);
        if(p.empty())
        {
            cout<<-1<<endl;
            return 0;
        }
        ans += p.top();
        p.pop();
    }
    cout<<ans<<endl;
    return 0;
}