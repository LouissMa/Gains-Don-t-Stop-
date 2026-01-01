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
    vector<pii> a(n);
    for(int i=0;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        a[i]={x,y};
    }
    sort(a.begin(),a.end(),[](pii a,pii b){
        return a.second > b.second;
    });
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        int x = a[i].first;
        int y = a[i].second;
        ans += x - y * i;
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