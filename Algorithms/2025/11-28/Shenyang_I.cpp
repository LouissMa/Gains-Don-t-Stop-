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
    cin>>n;
    vector<int> a(n-1);
    int ans = 0;
    int x;
    cin>>x;
    for(int i=0;i<n-1;i++) cin>>a[i];
    sort(a.begin(),a.end());
    int idx = upper_bound(a.begin(),a.end(),x) - a.begin();
    for(int i=idx;i<n-1;i++)
    {
        if(a[i] > x)
        {
            x += (a[i] - x + 1) / 2;
        }
    }
    cout<<x<<endl;
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