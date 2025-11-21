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
    vector<int> a(n+1),b(n+1);
    int cnt1 = 0,cnt2 = 0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i] == 1) cnt1++;
    }
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
        if(b[i] == 1) cnt2++;
    }
    for(int i=1;i<=n;i++)
    {
        if(i % 2 == 1)
        {
            if(cnt1 % 2 == 1) continue;
            else
            {
                int tt = a[i];
                if(a[i] == 1)
                {
                    cnt1 -= (b[i] == 0);
                    if(b[i] == 0) cnt2 ++;
                }
                else
                {
                    cnt1 += (b[i] == 1);
                    if(b[i] == 1) cnt2 --;
                }
            }
        }
        else
        {
            if(cnt2 % 2 == 1) continue;
            else
            {
                int tt = a[i];
                if(b[i] == 1)
                {
                    cnt2 -= (a[i] == 0);
                    if(a[i] == 0) cnt1 ++;
                }
                else
                {
                    cnt2 += (a[i] == 1);
                    if(a[i] == 1) cnt1 --;
                }
            }
        }
    }
    if(cnt1%2 == cnt2%2)
    {
        cout<<"Tie\n";
    }
    else
    {
        cout<<(cnt1%2 == 1 ? "Ajisai" : "Mai")<<"\n";
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