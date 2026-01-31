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
    string s1,s2;
    cin>>s1>>s2;
    bool ok = true;
    for(int i=0;i<n;i++)
    {
        if(s1[i] == s2[i]) continue;
        if((s1[i] == '0' && s2[i] == 'O') || (s1[i] == 'O' && s2[i] == '0')) continue;
        if(s1[i] == 'I')
        {
            if(s2[i] == 'l' || s2[i] == '1') continue;
        }
        if(s1[i] == 'l')
        {
            if(s2[i] == 'I' || s2[i] == '1') continue; 
        }
        if(s1[i] == '1')
        {
            if(s2[i] == 'l' || s2[i] == 'I') continue;
        }
        ok = false;
        break;
    }
    if(ok) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
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