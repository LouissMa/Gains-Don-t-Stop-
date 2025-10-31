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
    int n,k;
    cin>>n>>k;
    int ans = 0;
    vector<int> a(k+1);
    int sum = 0;
    for(int i=1;i<=k;i++)
    {
        int ty,c;
        cin>>ty>>c;
        a[ty] += c;
        sum += c;
    }
    if(n >= k)
    {
        cout<<sum<<endl;
        return;
    }
    sort(a.begin()+1,a.end(),greater<int>());
    for(int i=1;i<=n;i++)
    {
        ans += a[i];
    }
    cout<<ans<<endl;
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