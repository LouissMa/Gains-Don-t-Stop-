#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    vector<vector<int>> g(n + 1,vector<int>(m + 1));
    vector<int> p(n + 1);
    for(int i=1;i<=n;i++)
    {
        p[i] = i;
        for(int j=1;j<=m;j++) cin>>g[i][j];
    }
    int q;
    cin>>q;
    while(q --)
    {
        int x,y;
        cin>>x>>y;
        swap(p[x],p[y]);
    }
    for(int i=01;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cout<<g[p[i]][j]<<(j == m ? "" : " ");
        }
        cout<<'\n';
    }
    return 0;
}