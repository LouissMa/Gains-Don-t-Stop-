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
    int x = n;
    int k = 1;
    for(int i=2;i * i <= x;i++)
    {
        if(x % i == 0)
        {
            while(x % i == 0)
            {
                x /= i;
            }
            k *= i;
        }
    }
    if(x > 1) k *= x;
    cout<<k<<endl;
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