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
    int a,b,c;
    cin>>a>>b>>c;
    for(int i=0;i<5;i++)
    {
        int minn = min(a,b);
        minn = min(minn,c);
        if(a==minn) a++;
        else if(b==minn) b++;
        else c++;
    }
    cout<<a*b*c<<endl;
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