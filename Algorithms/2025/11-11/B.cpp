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
    string x;
    cin>>x;
    for(int i=0;i<n;i++)
    {
        if(x[i] == '1' && (i == 0 || i == n-1 || p[i] == 1 || p[i] == n))
        {
            cout<<-1<<"\n";
            return;
        }
    }
    int a = find(p.begin(), p.end(), 1) - p.begin() + 1;
    int b = find(p.begin(), p.end(), n) - p.begin() + 1;
    if(a > b) swap(a, b);
    cout << 5 << "\n";
    cout << 1 << " " << a << "\n";
    cout << 1 << " " << b << "\n";
    cout << a << " " << b << "\n";
    cout << a << " " << n << "\n";
    cout << b << " " << n << "\n";
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