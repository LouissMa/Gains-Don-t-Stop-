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

int f[3010][3010];
void solve() 
{
    string s;
    cin>>s;
    int n = s.size();
    int ans = 1e6;
    for(int l=n-1; l>=0; l--)
    {
        for(int r=l;r <= n-1;r++)
        {
            if(l == r)
            {
                f[l][r] = 0;
                continue;
            }
            f[l][r] = min(f[l+1][r],f[l][r-1]) + 1;
            f[l][r] = min(f[l][r],(s[l] != s[r]) + (r - l > 1 ? f[l+1][r-1] : 0));

        }
    }
    cout<<f[0][n-1]<<endl;
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