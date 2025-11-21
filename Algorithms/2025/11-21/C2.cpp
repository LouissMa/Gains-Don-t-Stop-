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
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    int flag = 0;
    int c;
    for(int j=19;j>-1;j--)
    {
        c = 0;
        for(int i=n-1;i>=0;i--)
        {
            if(a[i] >> j & 1) c^=1;
            if(b[i] >> j & 1) c^=1;
        }
        if(!c) continue;
        flag = 1;
        for(int i=n-1;i>=0;i--)
        {
            if((a[i] >> j & 1) != (b[i] >> j & 1))
            {
                if(i%2==0) cout<<"Ajisai\n";
				else cout<<"Mai\n";
                break;
            }
        }
        break;
    }
    if(!flag) cout<<"Tie\n";
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