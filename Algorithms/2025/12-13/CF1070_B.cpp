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
    string s;
    cin>>s;
    int p = -1;
    for(int i=0;i<n;i++)
    {
        if(s[i] == '1')
        {
            p = i;
            break;
        }
    }
    int cnt = 0;
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        if(s[(i+p)%n] == '1') cnt = 0;
        else cnt ++;
        ans = max(ans, cnt);
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