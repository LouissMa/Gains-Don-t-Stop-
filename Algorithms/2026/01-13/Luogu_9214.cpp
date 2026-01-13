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

const int N = 20;
struct node{
    int l,r,t;
}f[N];
bool vis[N];
bool flag;
int n;

void dfs(int deep,int now)
{
    if(deep == n)
    {
        flag = 1;
        return;
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i] && f[i].r < now) return;
        if(!vis[i] && f[i].r >= now)
        {
            vis[i] = true;
            if(f[i].l > now)
            {
                dfs(deep + 1,f[i].l + f[i].t);
            }
            else
            {
                dfs(deep + 1,now + f[i].t);
            }
            vis[i] = false;
        }
    }
}
void solve() 
{
    cin>>n;
    flag = 0;
    for(int i=1;i<=n;i++)
    {
        int k;
        cin>>f[i].l>>k>>f[i].t;
        f[i].r = f[i].l+k;
    }
    for(int i=1;i<=n;i++)
    {
        vis[i] = true;
        dfs(1,f[i].l + f[i].t);
        vis[i] = false;
    }
    if(flag) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
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