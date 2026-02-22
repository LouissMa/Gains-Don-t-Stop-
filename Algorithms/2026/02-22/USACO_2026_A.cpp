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

const int N = 1e5 + 10;
int n,k;
int a[N],b[N];
int nk,na[N],nb[N];
map<int,int> mp;
bool check(int val)
{
    nk = k;
    for(int i=1;i<=n;i++)
    {
        if(a[i] - b[i] >= val)
        {
            int dif = (a[i] - val - b[i] + 1) / 2;
            na[i] = a[i] - dif;
            nb[i] = b[i] + dif;
            nk -= dif;
        }
        else
        {
            na[i] = a[i];
            nb[i] = b[i];
        }
    }
    mp.clear();
    for(int i=1;i<=n;i++)
    {
        ++mp[na[i] - val];
        ++mp[nb[i]];
    }
    int vl = -n;
    int pos = -1e9;
    for(auto [ky,v] : mp)
    {
        if (vl <= 0) pos = ky; 
        vl += v;
    }
    int sm = 0;
    for(int i=1;i<=n;++i)
    {
        if(na[i]>=pos+val) sm+=na[i]-(pos+val);
        if(nb[i]<pos) sm+=pos-nb[i];
    }
    return sm<=nk;
}
void solve() 
{
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    int L=-1e20,R=1e9,res=1e9;
    while(L <= R)
    {
        int mid = (L + R) >> 1;
        if(check(mid))
        {
            res = mid;
            R = mid - 1;
        }
        else
        {
            L = mid + 1;
        }
    }   
    cout<<res<<endl;
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