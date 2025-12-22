#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5+10;
int d[N],s[N],h[N],flag;
bool vis[N];

int dfs(int now,int cnt)
{
    if(h[now] != 0) return cnt - 1 + h[now];
    if(vis[now] == true)
    {
        h[now] = cnt - s[now];
        flag = now;
        return cnt - 1;
    }
    vis[now] = true;
    s[now] = cnt;
    int ans = dfs(d[now],cnt+1);
    if(flag != 0)
    {
        if(now == flag) flag = 0;
        else h[now] = h[flag];
    }
    else h[now] = h[d[now]] + 1;
    vis[now] = false;
    return ans;
}
signed main()
{
    SPEED;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>d[i];
    for(int i=1;i<=n;i++)
    {
        cout<<dfs(i,1)<<"\n";
    }
    return 0;
}