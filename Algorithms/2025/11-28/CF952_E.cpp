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
    int x,y,z,k;
    cin>>x>>y>>z>>k;
    int ans = 0;
    for(int a = 1;a <= x;a++)
    {
        for(int b=1;b<=y;b++)
        {
            int c = k / a / b;
            if(a * b * c != k || c > z) continue;
            ans = max(ans,1LL * (x-a+1) * (y-b+1) * (z-c+1));
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