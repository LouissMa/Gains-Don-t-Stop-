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
    vector<int> a(n), b(n);
    vector<vector<int>> dp(n, vector<int>(2));
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    int l = 0,r = 0;
    for(int i=0;i<n;i++)
    {
        int minn = min(l - a[i],b[i] - r);
        int maxx = max(r - a[i],b[i] - l);
        l = minn;
        r = maxx;
    }
    cout<<r<<endl;
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