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
    vector<int> a(n);
    map<int,int> mp;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        mp[a[i]] ++;
    }
    int ans = n;
    vector<bool> st(n+1);
    for(int i=0;i<n;i++)
    {
        if(st[a[i]]) continue;
        int cnt = mp[a[i]];
        if(cnt < a[i])
        {
            ans -= cnt;
        }
        if(cnt > a[i])
        {
            ans -= cnt - a[i];
        }
        st[a[i]] = true;
    }
    cout<<n - ans<<endl;
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