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
    int n,m;
    cin>>n>>m;
    string s;
    cin>>s;
    vector<int> index(m);
    for(int i=0;i<m;i++)
    {
        cin>>index[i];
        index[i]--;
    }
    string c;
    cin>>c;
    sort(index.begin(),index.end());
    index.erase(unique(index.begin(),index.end()),index.end());
    m = index.size();
    sort(c.begin(),c.end());
    for(int i=0;i<m;i++)
    {
        s[index[i]] = c[i];
    }
    cout<<s<<endl;
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