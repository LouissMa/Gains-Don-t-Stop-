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
    string a,b;
    cin>>a>>b;
    int n =a.size();
    int m =b.size();
    int x = 0,y = 0;
    bool f1 = false,f2 = false;
    for(int i=0;i<n;i++)
    {
        if(a[i] == '+')
        {
            f1 = true;
            break;
        }
        x = x * 10 + a[i] - '0';
    }
    for(int i=0;i<m;i++)
    {
        if(b[i] == '+')
        {
            f2 = true;
            break;
        }
        y = y * 10 + b[i] - '0';
    }
    if(x > y)
    {
        cout<<"Yes\n";
    }
    else if(x < y) cout<<"No\n";
    else
    {
        if(f1) cout<<"Yes\n";
        else cout<<"No\n";
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