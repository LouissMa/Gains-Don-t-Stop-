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
    int ans = 0;
    int x;
    for(int i=2;i<=n;i++)
    {
        int res = 0;
        int tem = 0;
        while(1)
        {
            res += i;
            if(res > n) break;
            tem += res;
            if(ans < tem)
            {
                ans = tem;
                x = i;
            }
        }
    }
    cout<<x<<"\n";
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