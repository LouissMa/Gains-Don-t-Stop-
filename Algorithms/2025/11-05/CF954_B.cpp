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
    int n,m;
    cin>>n>>m;
    vector<vector<int>> a(n,vector<int>(m));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++) cin>>a[i][j];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            int maxx=0;
            if(i > 0)
            {
                maxx = max(maxx,a[i-1][j]);
            }
            if(i+1 < n)
            {
                maxx = max(maxx,a[i+1][j]);
            }
            if(j > 0)
            {
                maxx = max(maxx,a[i][j-1]);
            }
            if(j+1 < m)
            {
                maxx = max(maxx,a[i][j+1]);
            }
            if(a[i][j] > maxx) a[i][j] = maxx;
            cout<<a[i][j]<<" \n"[j == m-1];
        }
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