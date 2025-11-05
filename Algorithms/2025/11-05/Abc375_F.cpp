#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int inf = 1e18;
signed main()
{
    SPEED;
    int n,m,q;
    cin>>n>>m>>q;
    vector<int> A(m),B(m),C(m);
    for(int i=0;i<m;i++)
    {
        cin>>A[i]>>B[i]>>C[i];
        A[i]--;B[i]--;
    }
    vector<int> o(q),x(q),y(q);
    vector<bool> block(m,false);
    for(int i=0;i<q;i++)
    {
        cin>>o[i];
        if(o[i] == 1)
        {
            cin>>x[i];
            x[i]--;
            block[x[i]] = true;
        }
        else
        {
            cin>>x[i]>>y[i];
            x[i]--;y[i]--;
        }
    }
    vector<vector<int>> dist(n,vector<int>(n,inf));
    for(int i=0;i<n;i++) dist[i][i] = 0;
    for(int i=0;i<m;i++)
    {
        if(!block[i])
        {
            dist[A[i]][B[i]] = dist[B[i]][A[i]] = C[i];
        }
    }
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
            }
        }
    }
    vector<int> ans(q);
    for(int i=q-1;i>=0;i--)
    {
        if(o[i] == 2)
        {
            ans[i] = dist[x[i]][y[i]];
        }
        else
        {
            int j = x[i];
            for(int x=0;x<n;x++)
            {
                for(int y=0;y<n;y++)
                {
                    dist[x][y] = min({dist[x][y],dist[x][A[j]] + C[j] + dist[B[j]][y],
                                    dist[x][B[j]] + C[j] + dist[A[j]][y]});
                }
            }
        }
    }
    for(int i=0;i<q;i++)
    {
        if(o[i] == 2)
        {
            if(ans[i] == inf) cout<<-1<<endl;
            else cout<<ans[i]<<endl;
        }
    }
    return 0;
}