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
    int n,m,k;
    cin>>n>>m>>k;
    int l = k - 1;
    int r = n-k;
    int ans = 1;
    for(int a = 0;a <= l;a++)
    {
        int low =-1,high = r + 1;
        while(low + 1 < high)
        {
            int mid = (low + high)/2;
            if(a + mid +max(a,mid) - 1 <= m) low = mid;
            else high = mid;
        }
        if(low >= 0) ans = max(ans,a + low + 1);
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