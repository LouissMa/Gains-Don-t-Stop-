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

void solve() 
{
    int n,m;
    cin>>n>>m;
    vector<int> a(n),b(m);
    int sum1 = 0,sum2 = 0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        sum1 += a[i];
    }
    for(int i=0;i<m;i++)
    {
        cin>>b[i];
        sum2 += b[i];
    }
    if(sum1 == sum2)
    {
        cout<<1<<"\n";
        return;
    }
    int d = abs(sum1 - sum2);
    int ans = 0;
    int cur = 0;
    if(sum1 > sum2)
    {
        sort(a.rbegin(),a.rend());
        for(int x : a)
        {
            cur += x;
            ans++;
            if(cur >= d) break;
        }
    }
    else
    {
        sort(b.rbegin(),b.rend());
        for(int x : b)
        {
            cur += x;
            ans ++;
            if(cur >= d) break;
        }
    }
    cout<<ans<<"\n";
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