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

const int N = 2e5+10;
int n,dep[N],num[N],ans;
vector<int> vt[N];

void dfs(int x,int fa)
{
    num[dep[x]] ++;
    ans = max(ans,num[dep[x]]);
    int v = 1;
    for(auto &y : vt[x])
    {
        if(y != fa)
        {
            dep[y] = dep[x] + 1;
            v++;
            dfs(y,x);
        }
    }
    ans = max(ans,v);
    return;
}
void solve() 
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        vt[i].clear();
        num[i] = 0;
    }
    for(int i=1;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        a--; b--;
        vt[a].push_back(b);
        vt[b].push_back(a);
    }
    ans = 0;
    dep[0] = 0;
    dfs(0,-1);
    cout<<ans<<'\n';
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