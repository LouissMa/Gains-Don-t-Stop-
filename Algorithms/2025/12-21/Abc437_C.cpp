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
    int s = 0;
    for(int i=0;i<n;i++) 
    {
        int w,p;
        cin>>w>>p;
        a[i] = w + p;
        s += p;
    }
    sort(a.begin(),a.end());
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        if(s - a[i] >= 0)
        {
            s -= a[i];
            ans ++;
        }
    }
    cout<<ans<<endl;
}

signed main() 
{
    SPEED;
    int t;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}