#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5 + 10;
int h[N],e[N * 2],ne[N * 2],idx;
int n,ans = N;
bool st[N];
void add(int a,int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int dfs(int u)
{
    st[u] = true;
    int sum = 0,size = 0;
    for(int i=h[u];i!=-1;i=ne[i])
    {
        int j = e[i];
        if(st[j]) continue;
        int s = dfs(j);
        sum += s;
        size = max(size,s);
    }
    size = max(size,n - sum - 1);
    ans = min(ans,size);
    return sum + 1;
}
signed main()
{
    SPEED;
    cin>>n;
    memset(h,-1,sizeof h);
    idx = 0;
    for(int i=1;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        add(a,b);
        add(b,a);
    }
    dfs(1);
    cout<<ans<<endl;
    return 0;
}