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
    int n,m;
    cin>>n>>m;
    if(n == 1 || m == 1)
    {
        cout<<1<<"\n";
        return;
    }
    if(n <= 5)
    {
        if(m >= 5) 
        {
            cout<<3<<"\n";
        }
        else 
        {
            cout<<2<<"\n";
        }
        return;
    }
    if(m <= 5)
    {
        if(n >= 5)
        {
            cout<<3<<"\n";
        }
        else
        {
            cout<<2<<"\n";
        }
        return;
    }
    if(n >= 5 && m >= 5)
    {
        cout<<5<<"\n";
    }
    else
    {
        cout<<3<<"\n";
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