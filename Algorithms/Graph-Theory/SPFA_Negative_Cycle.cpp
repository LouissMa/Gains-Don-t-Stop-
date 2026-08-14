#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int N = 2010,M = 10010;
int n,m;
int h[N],e[M],ne[M],w[M],idx;
int dist[N],cnt[N];
bool st[N];

void add(int a,int b,int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool spfa()
{
    queue<int> q;
    for(int i=1;i<=n;i++)
    {
        st[i] = true;
        q.push(i);
    }
    
    while(q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false;
        
        for(int i=h[t];i!=-1;i= ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t]+w[i];
               cnt[j] = cnt[t]+1;
                if(cnt[j] >= n) return true;
                if(!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    return false;
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
    
    if(spfa()) puts("Yes");
    else puts("No");
    return 0;
}