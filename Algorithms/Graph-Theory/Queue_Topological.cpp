#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 510,M = 5010;
int h[N],e[M],ne[M],idx;
int n,m;
int d[N];
    
void add(int a,int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
void topsort()
{
    priority_queue<int,vector<int>,greater<int>> pq;
    vector<int> res;
    for(int i=1;i<=n;i++)
    {
        if(d[i] == 0) pq.push(i);
    }
    while(pq.size())
    {
        int t = pq.top();
        pq.pop();
        res.push_back(t);
        for(int i = h[t];~i;i = ne[i])
        {
            int j = e[i];
            d[j] --;
            if(d[j] == 0) pq.push(j);
        }
    }
    for(int i=0;i<n;i++) cout<<res[i]<<" \n"[i == n - 1];
}
signed main()
{
    SPEED;
    cin>>n>>m;
    memset(h,-1,sizeof h);
    idx = 0;
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        add(a,b);
        d[b] ++;
    }
    topsort();
    return 0;
}