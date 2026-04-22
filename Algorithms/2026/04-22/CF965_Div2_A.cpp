/*
Problem: Find K Distinct Points with Fixed Center
Contest: Codeforces Round 965 (Div. 2)
URL: https://codeforces.com/contest/1998/problem/A
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
    int x,y,k;
    cin>>x>>y>>k;
    for(int i=0;i<k;i++)
    {
        cout<<x - (k-1) + 2*i<<" "<<y - (k-1) + 2*i<<"\n";
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