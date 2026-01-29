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
    int n,s,x;
    cin>>n>>s>>x;
    int sum = 0;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        sum += a;
    }
    if(sum > s)
    {
        cout<<"NO\n";
        return;
    }
    if(sum == s)
    {
        cout<<"YES\n";
        return;
    }
    if((s - sum) % x == 0)
    {
        cout<<"YES\n";
    }
    else cout<<"NO\n";
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