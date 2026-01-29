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
    vector<int> p(n);
    for(int i=0;i<n;i++) cin>>p[i];
    int i = 0;
    while(i < n && p[i] == n - i) i++;
    if(i < n)
    {
        int j = find(p.begin() + i,p.end(),n - i) - p.begin();
        reverse(p.begin() + i,p.begin() + j + 1);   
    }
    for(int i=0;i<n;i++) cout<<p[i]<<" \n"[i==n-1];
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