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

const int N = 510;
int a[N],maxx[N];
void solve() 
{
    int n;
    cin>>n;
    int pos = 0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        maxx[i] = max(maxx[i-1],a[i]);
        if(a[i] == maxx[i])
        {
            pos = i;
        }
    }
    int cnt = 0;
    for(int i=1;i<=n;i++)
    {
        if(i == maxx[i]) cnt ++;
    }
    if(cnt == 0)
    {
        for(int i=1;i<=n;i++) cout<<a[i]<<" \n"[i==n];
        return;
    }
    swap(a[1],a[pos]);
    for(int i=1;i<=n;i++) cout<<a[i]<<" \n"[i==n];
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