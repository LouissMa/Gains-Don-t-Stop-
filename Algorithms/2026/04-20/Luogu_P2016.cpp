#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2000;
int n,f[N][2];
int fa[N];
vector<int> e[N];

void dfs(int u)
{
    f[u][0] = 0;
    f[u][1] = 1;
    if(e[u].size() == 0) return;
    for(int v : e[u])
    {
        dfs(v);
        f[u][0] += f[v][1];
        f[u][1] += min(f[v][0],f[v][1]);
    }
}
signed main()
{
    SPEED;
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int a,k;
        cin>>a>>k;
        a ++;
        if(k == 0) continue;
        for(int i=1;i<=k;i++)
        {
            int z;
            cin>>z;
            z ++;
            e[a].push_back(z);
            fa[z] = a;
        }
    }
    int root;
    for(int i=1;i<=n;i++)
    {
        if(fa[i] == 0)
        {
            root= i;
            break;
        }
    } 
    dfs(root);
    cout<<min(f[root][0],f[root][1])<<"\n";
    return 0;
}