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
    int n = 5;
    vector<int> a(n);
    int cnt = 0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        if(a[i] != 0) cnt++;
    }
    int k;
    cin>>k;
    if(cnt == 0)
    {
        cout<<"1/1000\n";
        return;
    }
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        if(a[i] == k) ans++;
    }
    if(ans == cnt)
    {
        cout<<"1/1\n";
        return;
    }
    if(ans == 0)
    {
        cout<<"0/1\n";
        return;
    }
    cout<<ans<<"/"<<cnt<<"\n";
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