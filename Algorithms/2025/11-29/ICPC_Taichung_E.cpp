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

int p[6],xx[6],yy[6];
void solve() 
{
    int n,j,k;
    cin>>n>>j>>k;
    int x;
    if(n == 12) x = 2;
    if(n == 123) x = 3;
    if(n == 1234) x = 4;
    for(int i=1;i<=x;i++) p[i] = i;
    int cnt = 0;
    do{
        cnt++;
        if(j == cnt)
        {
            for(int i=1;i<=x;i++) xx[i] = p[i];
        }
        if(k == cnt) 
        {
            for(int i=1;i<=x;i++) yy[i] = p[i];
        }
    }while(next_permutation(p+1,p+1+x));
    int ans = 0;
    for(int i=1;i<=x;i++)
    {
        if(xx[i] == yy[i]) ans++;
    }
    cout<<ans<<"A"<<x-ans<<"B"<<endl;
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