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
    int n,c;
    cin>>n>>c;
    c --;
    vector<string> s(n);
    for(int i=0;i<n;i++) cin>>s[i];
    vector<int> end(n,-1);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(s[i][j] == '#')
            {
                end[j] = i;
            }
        }
    }
    vector<vector<int>> f(n, vector<int>(n, 0));
    vector<vector<int>> g(n, vector<int>(n, 0));
    f[n-1][c] = 1;
    for(int i=n - 1;i>0;i--)
    {
        for(int j=0;j<n;j++)
        {
            if(f[i][j])
            {
                f[i-1][j] = 1;
            }
            if(g[i][j] && s[i-1][j] == '.')
            {
                g[i-1][j] = 1;
            }
            if(j && (f[i][j] || g[i][j]))
            {
                if(end[j-1] <= i - 1)
                {
                    f[i-1][j-1] = 1;    
                }
                if(s[i-1][j-1] == '.') g[i-1][j-1] = 1;
            }
            if(j + 1 < n && (f[i][j] || g[i][j]))
            {
                if(end[j + 1] <= i - 1) f[i-1][j+1] = 1;
                if(s[i-1][j+1] == '.') g[i-1][j+1] = 1;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        cout<<(f[0][i] | g[0][i]);
    }
    cout<<"\n";
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