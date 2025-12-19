#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
int h[50001],ne[50001],w[50001],to[50001],en=0;
int n,m,S,T;
int dis[10001];
inline void add(int a,int b,int c)
{ne[en]=h[a];w[en]=c;to[en]=b;h[a]=en++;}
inline bool SPFA(int mid)
{
    memset(dis,0x3f,sizeof dis);
    queue<int>q;
    q.push(S);
    dis[S]=1;
    while (!q.empty())
    {
        int x=q.front();q.pop();
        for (int i=h[x];i>=0;i=ne[i])
        if (w[i]<=mid){
            if (dis[to[i]]==0x3f3f3f3f)
            {
                dis[to[i]]=1;
                q.push(to[i]);
            }
        }
    }
    if (dis[T]==0x3f3f3f3f) return false;
    else return true;
}
int main()
{
    memset(h,-1,sizeof h);
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for (int i=1;i<=m;++i)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
        add(b,a,c);
    }
    int l=0,r=10000;
    while (l<r)
    {
        int mid=(l+r)/2;
        if (SPFA(mid)) r=mid;
        else l=mid+1;
    }
    printf("%d\n",l);
}