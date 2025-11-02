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
    vector<int> a(k);
    for(int i=0;i<k;i++) cin>>a[i];
    sort(a.begin(),a.end());
    int ans = 0;
    int cnt1 = 0;
    for(int i=0;i<k-1;i++)
    {
        ans += (a[i] - 1);
        cnt1 += a[i];
    }
    cout<<ans + cnt1<<endl;
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