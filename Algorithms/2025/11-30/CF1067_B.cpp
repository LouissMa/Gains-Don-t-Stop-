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
    vector<int> a(2 * n);
    map<int,int> mp;
    for(int i=0;i<2 * n;i++)
    {
        cin>>a[i];
        mp[a[i]] ++;
    }
    int cnt1 = 0,cnt2 = 0;
    for(int i=0;i<=2 * n;i++)
    {
        if(mp[i] == 0) continue;
        if(mp[i] % 2 == 0) cnt2 ++;
        else cnt1 ++;
    }
    if(cnt1 == 0 && cnt2 % 2 != n % 2)
    {
        cout<<(cnt2 - 1) * 2<<endl;
    }
    else cout<<cnt2 * 2 + cnt1<<endl;
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