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
const int MOD = 998244353;
void solve() 
{
    int n;
    cin>>n;
    vector<int> a(n),b(n);
    int minn = 1e18;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++)
    {
        cin>>b[i];
        minn = min(minn,b[i]);
    }    
    int cnt = 0;
    for(int i=0;i<n;i++)
    {
        if(a[i] > minn) cnt++;
    }
    int x1 = cnt;
    int x2 =n - cnt;
    int res1 = 1,res2 = 1;
    for(int i=1;i<=x1;i++)
    {
        res1 = res1 * i % MOD;
    }
    for(int i=1;i<=x2;i++)
    {
        res2 = res2 * i % MOD;
    }
    cout<<res1 * res2 % MOD<<endl;
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