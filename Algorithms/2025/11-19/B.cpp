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
    vector<int> r(n),c(m);
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < m; j++) {
            r[i] += s[j] - '0';
            c[j] += s[j] - '0';
        }
    }
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < m; j++) {
            r[i] -= s[j] - '0';
            c[j] -= s[j] - '0';
        }
    }
    bool ok = true;
    for (int i = 0; i < n; i++) {
        if (r[i] % 3 != 0) {
            ok = false;
        }
    }
    for (int j = 0; j < m; j++) {
        if (c[j] % 3 != 0) {
            ok = false;
        }
    }
    if(ok)
    {
        cout<<"YES"<<endl;
    }
    else
    {
        cout<<"NO"<<endl;
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