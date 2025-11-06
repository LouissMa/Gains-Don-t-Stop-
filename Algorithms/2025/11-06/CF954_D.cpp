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
    string s;
    cin>>s;
    s = " " + s;
    vector<int> f1(n+10, 0), f2(n+10, 0);
    if(n == 2)
    {
        int tem = (s[1] - '0') * 10;
        tem += (s[2] - '0');
        cout<<tem<<"\n";
        return;
    }
    f1[1] = s[1] - '0';
    f2[2] = (s[1] - '0') * 10 + (s[2] - '0');
    for(int i=2;i<=n;i++)
    {
        f1[i] = min(f1[i-1] + s[i] - '0',f1[i-1] * (s[i] - '0'));
        if(i != 2)
        {
            f2[i] = min(min(f1[i-2] + (s[i-1] - '0') * 10 +(s[i]-'0'),f1[i-2] * ((s[i-1] - '0') * 10 +(s[i]-'0'))),min(f2[i-1] + (s[i] - '0'),f2[i-1] * ((s[i] - '0'))));
        }
    }
    cout<<f2[n]<<"\n";
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