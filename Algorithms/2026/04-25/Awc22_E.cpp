//deliverydriversroute.cpp
#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(), (x).end()

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin>>n>>m;

    const long long int inf=(1LL<<60);
    vector<vector<long long int>> edge(n, vector<long long int>(n, inf));
    for(int i=0;i<n;i++){
        edge[i][i]=0;
    }
    for(int i=0;i<m;i++){
        int u, v, w;
        cin>>u>>v>>w;
        u--; v--;
        edge[u][v]=w;
        edge[v][u]=w;
    }

    vector<vector<long long int>> dist=edge;
    for(int s=0;s<n;s++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                dist[i][j]=min(dist[i][j], dist[i][s]+dist[s][j]);
            }
        }
    }

    vector<vector<long long int>> bitDP(1<<n, vector<long long int>(n, inf));
    for(int i=0;i<n;i++){
        if(edge[0][i]!=inf) bitDP[1<<i][i]=dist[0][i];
    }
    for(int mask=1;mask<(1<<n);mask++){
        for(int j=0;j<n;j++){
            if((mask&(1<<j))==(1<<j)) continue;
            int nmask=mask|(1<<j);

            for(int i=0;i<n;i++){
                if((mask&(1<<i))!=(1<<i)) continue;
                if(dist[i][j]==inf) continue;
                bitDP[nmask][j]=min(bitDP[nmask][j], bitDP[mask][i]+dist[i][j]);
            }
        }
    }

    long long int mn=inf;
    for(int i=0;i<n;i++){
        mn=min(mn, bitDP.back()[i]+dist[i][0]);
    }

    if(mn==inf) cout<<-1<<'\n';
    else cout<<mn<<'\n';
    return 0;
}