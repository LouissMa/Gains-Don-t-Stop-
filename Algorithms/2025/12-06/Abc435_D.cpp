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
    vector<vector<int>> adj(n),rev(n);
    vector<int> a(n,0);
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        u--;v--;
        adj[u].push_back(v);
        rev[v].push_back(u);
    }
    int q;
    cin>>q;
    vector<bool> can_reach_black(n, false);
    vector<bool> is_black(n, false);
    while(q--)
    {
        int op,x;
        cin>>op>>x;
        x--;
        if(op == 1)
        {
            if(!is_black[x])
            {
                is_black[x] = true;
                if(!can_reach_black[x])
                {
                    queue<int> p;
                    p.push(x);
                    can_reach_black[x] = true;
                    while(!p.empty())
                    {
                        int u = p.front();
                        p.pop();
                        for(auto v : rev[u])
                        {
                            if(!can_reach_black[v])
                            {
                                can_reach_black[v] = true;
                                p.push(v);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if(can_reach_black[x]) cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
        }
    }
}