#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin>>n;
    vector<std::vector<int>> e(n);
    vector<int> id(n - 1, -1);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        cin>>u>>v;
        u --;
        v --;
        e[u].push_back(i);  // 节点u连接边i
        e[v].push_back(i);  // 节点v连接边i
    }
    int c = 0;
    for(int i=0;i<n;i++)
    {
        if(e[i].size() >= 3)
        {
            for(int j=0;j<3;j++)
            {
                id[e[i][j]] = j;
            }   
            c = 3;
            break;
        }
    }
    for(int i=0;i<n-1;i++)
    {
        if(id[i] == -1) id[i] = c++;
    }
    for(int i=0;i<n-1;i++) cout<<id[i]<<"\n";
    return 0;
}