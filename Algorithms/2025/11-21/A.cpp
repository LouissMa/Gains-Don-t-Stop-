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
    set<int> v;
    if(n % 2 == 1)
    {
        cout<<0<<endl;
        return;
    }
    for(int x = 0;x <= n/2;x ++)
    {
        int leg2 = n/2 - x;
        if(leg2 % 2 == 0)
        {
            leg2 /= 2;
            if(v.count(leg2))
            {
                continue;
            }
            else 
            {
                v.insert(leg2);
                ans ++;
            }
        }
        else continue;
    }
    cout<<ans<<endl;
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