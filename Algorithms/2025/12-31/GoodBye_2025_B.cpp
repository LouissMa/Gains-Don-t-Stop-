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
    string r;
    cin>>r;
    int ans = 0;
    int n = r.size();
    if(r[0] == 'u')
    {
        ans++;
        r[0] = 's';
    }
    if(r[n-1] == 'u')
    {
        ans++;
        r[n-1] = 's';
    }
    for(int i=0,j=0;i<n;i++)
    {
        if(r[i] == 's')
        {
            ans += (i-j-1)/2;
            j = i;
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