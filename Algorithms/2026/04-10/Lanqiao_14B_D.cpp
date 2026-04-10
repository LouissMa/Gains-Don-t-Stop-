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

int n;
const int N = 20;
int t[N],d[N],l[N],f[N];
bool ok;

void dfs(int x,int tim)
{
    if(ok) return;
    if(x == n)
    {
        ok = true;
        return;
    }
    for(int i=1;i<=n;i++)
    {
        if(f[i] == 0 && tim <= t[i] + d[i])
        {
            f[i] = 1;
            dfs(x + 1,max(t[i],tim) + l[i]);
            if(ok) return;
            f[i] = 0;
        }
    }
}
void solve() 
{   
    ok = 0;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>t[i]>>d[i]>>l[i];
    dfs(0,0);
    if(ok) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
}

signed main() 
{
    SPEED;
    int T;
    cin >> T;
    while(T--) 
    {
        solve();
    }
    return 0;
}