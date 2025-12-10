/*
Problem: Problem Title
Contest: Contest Name
URL: URL
Memory Limit: 1024 MB
Time Limit: 2000 ms

Description:
Paste problem statement here
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

const int N = 2e5 + 10;
int v[N],l[N],t[N],ans[N];
int id[N];
void solve() 
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>v[i];
    sort(v+1,v+n+1);
    for(int i=1;i<=n;i++) cin>>l[i];
    sort(l+1,l+n+1,greater<int>());
    int q;
    cin>>q;
    for(int i=1;i<=q;i++)
    {
        cin>>t[i];
        id[i] = i;
    }
    sort(id + 1, id + q + 1, [&](int x, int y) { return t[x] < t[y]; });
    int sum = 0, suml = 0; int pos = 1;
    for (int i = 1; i <= n; i++) sum += v[i], suml += l[i];
    for(int _ = 1; _ <= q; _++)
    {
        int i = id[_];
        while(pos <= n && v[pos] <= t[i] * l[pos])
        {
            sum -= v[pos];
            suml -= l[pos];
            pos++;
        }
        ans[i] = sum - suml * t[i];
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<" \n"[i == q];  
}

signed main() 
{
    SPEED;
    int t = 1;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}