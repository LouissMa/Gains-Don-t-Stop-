#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int,int> PII;
const int N = 1e6+10;
int h[N],e[N],ne[N],w[N],idx;
int dist[N];
bool st[N];
int n,m;

void add(int a,int b,int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int dijkstra()
{
    memset(dist,0x3f,sizeof dist);
    dist[1] =0;
    
    priority_queue<PII,vector<PII>,greater<PII>> heap;
    heap.push({0,1});
    
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        
        int u = t.first,v = t.second;
        if(st[v]) continue;
        st[v] = true;
        for(int i = h[v];i!=-1;i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[v] + w[i])
            {
                dist[j] = dist[v] + w[i];
                heap.push({dist[j],j});
            }
        }
    }
    
    if(dist[n] == 0x3f3f3f3f) return -1;
    else return dist[n];
}

int main()
{
    cin>>n>>m;
    memset(h,-1,sizeof h);
    while(m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c);
    }
    
    cout<<dijkstra()<<endl;
    return 0;
}