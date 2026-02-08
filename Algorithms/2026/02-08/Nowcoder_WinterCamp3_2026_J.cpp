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
    int n,q;
    cin>>n>>q;
    while(q--)
    {
        int x;
        cin>>x;
        int k = __lg(x);
        int L = 1LL << k;
        int R = (L << 1) - 1;
        int realR = min(R,n);
        cout<<realR - L + 1<<"\n";
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