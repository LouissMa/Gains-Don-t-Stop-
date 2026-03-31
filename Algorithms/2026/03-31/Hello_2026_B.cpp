/*
Problem: 
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
    vector<int> a(n),b(n+1);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        if(a[i] < n) b[a[i]] ++;
    }
    int mex = 0;
    while(mex < n && b[mex] > 0) mex++;
    cout<<min(mex,k-1)<<'\n';
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