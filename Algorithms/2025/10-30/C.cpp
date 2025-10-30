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
    for(int i=0;i<n;i++) cin>>a[i];
    bool ok = false;
    for(int i=1;i<n;i++)
    {
        if(a[i] % 2 != a[i-1] % 2) 
        {
            ok = true;
            break;
        }
    }
    if(!ok)
    {
        for(int i=0;i<n;i++) cout<<a[i]<<" \n"[i==n-1];
    }
    else
    {
        sort(a.begin(),a.end());
        for(int i=0;i<n;i++) cout<<a[i]<<" \n"[i==n-1];
    }
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