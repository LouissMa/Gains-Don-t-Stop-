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
    int ans = 1e18;
    for(int st = 0;st <= 1;st++)
    {
        int t_val = st;
        char c = '0' + st;
        int cnt1 = 0,cnt0 = 0;
        for(int i=0;i<n;i++)
        {
            if(s[i] == '1' && c == '0')
            {
                cnt1 ++;
                if(cnt0 > 0) cnt0 --;
            }
            else if(s[i] == '0' && c == '1')
            {
                cnt0 ++;
                if(cnt1 > 0) cnt1 --;
            }
            t_val = 1 - t_val;
            c = '0' + t_val;
        }
        int cur = cnt0 + cnt1;
        ans = min(ans,cur);
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