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
    int x1, y1, x2, y2;
    cin>>x1>>y1>>x2>>y2;
    if((x1 < y1 && x2 > y2) || (x1 > y1 && x2 < y2))
    {
        cout<<"NO\n";
    }
    else
    {
        cout<<"YES\n";
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