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

bool isPrime(int x)
{
    if(x < 2) return false;
    for(int i=2;i<=x/i;i++)
    {
        if(x%i == 0) return false;
    }
    return true;
}
void solve() 
{
    int a,b;
    cin>>a>>b;
    if(b-a != 2)
    {
        cout<<"N\n";
        return;
    }
    if(isPrime(a) && isPrime(b))
    {
        cout<<"Y\n";
    }
    else
    {
        cout<<"N\n";
    }
}

signed main() 
{
    SPEED;
    int t;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}