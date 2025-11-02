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
    int q;
    cin>>q;
    int ans = 0;
    for(int i=0;i<n-3;i++)
    {
        ans += s.substr(i,4) == "1100";
    }
    while(q--)
    {
        int p;
        cin>>p;
        p--;
        char v;
        cin>>v;
        for(int j = max(0LL,p-3);j<=min(p,n-4);j++)
        {
            ans -= s.substr(j,4) == "1100";
        }
        s[p] = v;
        for(int j = max(0LL,p-3);j<=min(p,n-4);j++)
        {
            ans += s.substr(j,4) == "1100";
        }
        cout<<(ans?"YES":"NO")<<endl;
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