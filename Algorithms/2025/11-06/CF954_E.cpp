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
    int n,k;
    cin>>n>>k;
    int ans = 0;
    int odd = 0;
    map<int,vector<int>> f;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        f[a%k].push_back(a);
    }
    for(auto &[_,a] : f){
        sort(a.begin(),a.end());
        if(a.size() % 2 == 0)
        {
            for(int i=0;i<a.size();i+=2)
            {
                ans += (a[i+1] - a[i])/k;
            }
        }
        else
        {
            odd++;
            int sum = 0;
            for(int i=1;i<a.size();i+=2)
            {
                sum += (a[i+1] - a[i])/k;
            }
            int res = sum;
            for(int i=0;i+1<a.size();i+=2)
            {
                sum += (a[i+1] - a[i])/k;
                sum -= (a[i+2] - a[i+1])/k;
                res = min(res, sum);
            }
            ans += res;
        }
    }
    if(odd > 1)
    {
        ans = -1;
    }
    cout<<ans<<"\n";
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