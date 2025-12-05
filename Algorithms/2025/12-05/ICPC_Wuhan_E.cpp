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
    int cnt1 = 0,cnt2 = 0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        if(a[i] & 1) cnt1 ++;
    }
    for(int i=0;i<n;i++)
    {
        cin>>b[i];
        if(b[i] & 1) cnt2 ++;
    }
    if(cnt1 != cnt2)
    {
        cout<<"No\n";
        return;
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    bool ok = 1;
    for(int i=0;i<n;i++)
    {
        if(a[i] != b[i])
        {
            ok = 0;
            break;
        }
    }
    if(ok == 1)
    {
        cout<<"Yes\n";
        return;
    }
    bool f1 = 0,f2 = 0;
    for(int i=0;i<n-1;i++)
    {
        f1 |= (a[i] + 1 == a[i+1]);
        f2 |= (b[i] + 1 == b[i+1]);
    }
    if(f1 && f2)
    {
        cout<<"Yes\n";
    }
    else
    {
        cout<<"No\n";
    }
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