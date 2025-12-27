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
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    int ans = 0;
    for(int i=0;i<n-1;i++) ans += abs(a[i] - a[i+1]);
    int maxx = max(abs(a[0] - a[1]), abs(a[n-1] - a[n-2]));
    for(int i=1;i<n-1;i++) 
    {
        int cur = abs(a[i-1]-a[i]) + abs(a[i]-a[i+1]) - abs(a[i-1] - a[i+1]);
        maxx = max(maxx,cur);
    }
    cout << ans - maxx << "\n";
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