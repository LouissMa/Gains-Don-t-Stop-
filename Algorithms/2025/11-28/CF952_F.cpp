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
    int h,n;
    cin>>h>>n;
    vector<int> a(n),c(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>c[i];
    int l = 0,r = 1e11;
    while(l < r)
    {
        int x = (l+r)/2;
        int dmg = 0;
        for(int i=0;i<n;i++)
        {
            dmg += (x + c[i] - 1) / c[i] * a[i];
            if(dmg >= h) break;
        }
        if(dmg >= h) r = x;
        else l = x + 1;
    }
    cout<<l<<"\n";
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