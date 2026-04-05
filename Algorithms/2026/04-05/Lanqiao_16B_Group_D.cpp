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
    int A, B, C, K;
    cin >> A >> B >> C >> K;
    while(K --)
    {
        int a = (B + C) >>1;
        int b = (A + C) >> 1;
        int c = (A + B) >> 1;
        if(a == b && b == c) break;
        A = a;
        B = b;
        C = c;
    }
    cout << A << " " << B << " " << C << endl;
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