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
    vector<int> a(n);
    int maxx = 0;
    int pos = -1;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        maxx = max(maxx, a[i]);
    }
    int num = n - 2;
    cout<<a[0] + a[n-1] + num * maxx<<"\n";
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