#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5+10;
int n,m;
int indeg[N];
signed main()
{
    SPEED;
    cin>>n>>m;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        a--;b--;
        indeg[b]++;
        adj[a].push_back(b);
    }
    priority_queue<int, vector<int>, greater<int>> q;
    for(int i=0;i<n;i++)
    {
        if(indeg[i] == 0) q.push(i);
    }
    vector<int> ans;
    while(!q.empty())
    {
        int t = q.top();
        q.pop();
        ans.push_back(t+1);
        for(auto x : adj[t])
        {
            indeg[x] --;
            if(indeg[x] == 0) q.push(x);
        }
    }
    if(ans.size() != n)
    {
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    for(int i=0;i<n;i++)
    {
        cout<<ans[i]<<" \n"[i==n-1];
    }
    return 0;
}