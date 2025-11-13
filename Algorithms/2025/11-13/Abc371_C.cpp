#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int N;
    cin>>N;
    int MG;
    cin>>MG;
    vector<vector<int>> G(N,vector<int>(N,0));
    for(int i=0;i<MG;i++)
    {
        int u,v;
        cin>>u>>v;
        u--;
        v--;
        G[u][v] = 1;
        G[v][u] = 1;
    }
    int MH;
    cin>>MH;
    vector<vector<int>> H(N,vector<int>(N,0));
    for(int i=0;i<MH;i++)
    {
        int u,v;
        cin>>u>>v;
        u--;
        v--;
        H[u][v] = 1;
        H[v][u] = 1;
    }
    vector<vector<int>> A(N,vector<int>(N,0));
    for(int i=0;i<N;i++)
    {
        for(int j=i+1;j<N;j++)
        {
            cin>>A[i][j];
        }
    }
    vector<int> P(N);
    iota(P.begin(),P.end(),0);
    int ans = 1e9;
    do{
        int res = 0;
        for(int i=0;i<N;i++)
        {
            for(int j=i+1;j<N;j++)
            {
                if(H[i][j] != G[P[i]][P[j]])
                {
                    res += A[i][j];
                }
            }
        }
        ans = min(ans,res);
    }while(next_permutation(P.begin(),P.end()));
    cout<<ans<<endl;
    return 0;
}