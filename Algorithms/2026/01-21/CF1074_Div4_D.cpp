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

const int N = 2e5 + 10;
int a[N],b[N],c[N];

void solve() 
{
    int n,m,h;
    cin>>n>>m>>h;
    for(int i=0;i<n;i++) cin>>a[i];
    int p = 0;
    for(int i=0;i<m;i++) 
    {
        cin>>b[i]>>c[i];
        b[i] --;
        a[b[i]] += c[i];
        if(a[b[i]] > h)
        {
            for(int j=p;j<=i;j++) a[b[j]] -= c[j];
            p = i + 1;
        }
    }
    for(int i=0;i<n;i++) cout<<a[i]<<" \n"[i==n-1];
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