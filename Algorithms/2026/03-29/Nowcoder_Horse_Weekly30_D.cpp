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
    int n,m,k;
    cin>>n>>m>>k;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    int l = 0,r = m,R = 0;
    while(l <= r)
    {
        int mid = l + (r - l) / 2;
        int sum = 0;
        for(int i=0;i<n;i++) sum += min(a[i],mid);
        if(sum <= k)
        {
            R= mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    int cnt = 0;
    for(int i=0;i<n;i++)
    {
        int tt = min(a[i],R);
        cnt += tt;
        a[i] -= tt;
    }
    k -= cnt;
    if(k > 0 && R < m)
    {
        for(int i=0;i<n;i++)
        {
            if(k == 0) break;
            if(a[i] > 0)
            {
                a[i] --;
                k --;
            }
        }
    }
    if(k > 0)
    {
        int l1 = 0,r1 = 1e9;
        int v = 0;
        while(l1 <= r1)
        {
            int mid = l1 + (r1 - l1) / 2;
            int sum = 0;
            for(int i=0;i<n;i++)
            {
                if(a[i] >= mid)
                {
                    sum += (a[i] - mid);
                }
            }
            if(sum <= k)
            {
                v = mid;
                r1 = mid - 1;
            }
            else l1 = mid + 1;
        }
        int cnt2 = 0;
        for(int i=0;i<n;i++)
        {
            if(a[i] >= v)
            {
                cnt2 += (a[i] - v);
                a[i] = v;
            }
        }
        k -= cnt2;
        if(k > 0)
        {
            for(int i=0;i<n;i++)
            {
                if(k == 0) break;
                if(a[i] == v)
                {
                    a[i] --;
                    k --;
                }
            }
        }
    }
    for(int i=0;i<n;i++) cout<<a[i]<<" \n"[i==n-1];
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