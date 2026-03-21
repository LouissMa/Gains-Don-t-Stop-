#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2e5 + 10;
int n,t[N],ans[N];
bool vis[N];

int dfs(int u)
{
    if(ans[u]) return ans[u];
    if(vis[u])
    {
        int len = 1;
        int v = t[u];
        while(v != u)
        {
            len ++;
            v = t[v];
        }
        ans[u] = len;
        v = t[u];
        while(v != u)
        {
            ans[v] = len;
            v = t[v];
        }
    }
}
signed main()
{
    SPEED;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>t[i];
    for(int i=)
}