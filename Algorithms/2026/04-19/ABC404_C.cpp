/*
Problem: Cycle Graph?
Contest: AtCoder Beginner Contest 404
URL: https://atcoder.jp/contests/abc404/tasks/abc404_c
Memory Limit: 1024 MB
Time Limit: 2000 ms

Description:
Paste problem statement here
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2e5+10;
int n,m;
int d[N];
vector<int> g[N];
int f[N];

int find(int u)
{
    if(f[u]==u)return u;
    return f[u]=find(f[u]);
}

void me(int u,int v)
{
    f[find(u)] = find(v);
}
signed main()
{
    SPEED;
    cin>>n>>m;
    for(int i=1;i<=n;i++) f[i] = i;
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
        me(u,v);
    }
    int ok = 1;
    for(int i=1;i<=n;i++) if(g[i].size()>2) ok = 0;
    int t = find(1);
    for(int i=1;i<=n;i++)
    {
        if(find(i) != t) ok = 0;
    }
    cout<<(ok?"Yes":"No")<<endl;
    return 0;
}