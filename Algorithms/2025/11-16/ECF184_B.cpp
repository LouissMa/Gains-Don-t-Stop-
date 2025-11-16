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
    string s;
    cin>>s;
    int n = s.size();
    int ok = 0;
    for(int i=0;i<n-1;i++)
    {
        if(s[i] != '<' && s[i+1] != '>') ok = 1;
    }
    if(ok)
    {
        cout<<-1<<"\n";
        return;
    }
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        if(s[i] != '>') ans = max(ans,i+1);
        if(s[i] != '<') ans = max(ans,n-i);
    }
    cout<<ans<<"\n";
    return;
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