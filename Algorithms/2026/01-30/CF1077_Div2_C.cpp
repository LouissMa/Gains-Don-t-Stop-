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

const int N = 2e5 +10;
int a1[N],a2[N];
int n;
void solve() 
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a1[i];
    for(int i=1;i<=n;i++) a2[i] = a1[i];
    sort(a1+1,a1+n+1);
    auto check = [&](int x) -> bool
    {
        int l = 1,r = n;
        while(l < r)
        {
            int mid = (l + r + 1) >> 1;
            if(a1[mid] - a1[1] < x) l = mid;
            else r = mid - 1;
        }
        int qr = l;
        l = 1,r = n;
        while(l < r)
        {
            int mid = (l + r) >> 1;
            if(a1[n] - a1[mid] < x) r = mid;
            else l = mid + 1;
        }
        int ql = l;
        for(int i=ql;i<=qr;i++)
        {
            if(a1[i] != a2[i]) return false;
        }
        return true;
    };
    int L = 1,R = 2e9;
    while(L < R)
    {
        int mid = (L + R + 1) >> 1;
        if(check(mid)) L = mid;
        else R = mid - 1;
    }
    if(L == 2e9) cout<<-1<<endl;
    else cout<<L<<endl;
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