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

const int N=2e5+10;
int p[N];
int find(int x)
{
    if(p[x]!=x)p[x]=find(p[x]);
    return p[x];
}
void solve() 
{
    int n;
    cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    vector<int> suf(n+1);
    suf[n] = a[n];
    for(int i=n-1;i>=1;i--) suf[i] = max(a[i],suf[i+1]);
    vector<int> s(n + 1);
    for(int i=1;i<=n;i++)
    {
        int l = i,r = n;
        while(l < r)
        {
            int mid = (l + r + 1) >> 1;
            if(suf[mid] >= a[i]) l = mid;
            else r = mid - 1;
        }
        s[i]++;
        s[l] --;
    }
    int ans = 0;
    for(int i=1;i<n;i++)
    {
        ans += s[i];
        if(ans <= 0)
        {
            cout<<"NO"<<endl;
            return;
        }
    }
    cout<<"YES"<<endl;
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