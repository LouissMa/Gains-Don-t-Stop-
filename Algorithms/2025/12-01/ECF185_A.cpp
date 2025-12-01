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
    vector<vector<int>> g(n,vector<int>(n));
    int value = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            g[i][j] = value;
            value++;
        }
    }
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            int sum = g[i][j];
            if(i - 1 >= 0) sum += g[i-1][j];
            if(j - 1 >= 0) sum += g[i][j-1];
            if(i + 1 < n) sum += g[i+1][j];
            if(j + 1 < n) sum += g[i][j+1];
            ans = max(ans,sum);
        }
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