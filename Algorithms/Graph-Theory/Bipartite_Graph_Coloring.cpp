#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 100010,M = 200010;
int n,m;
int color[N];
int h[N],e[M],ne[M],idx;

void add(int a,int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool dfs(int u,int c)
{
    color[u] = c;
    
    for(int i=h[u];i!=-1;i = ne[i])
    {
        int j = e[i];
        if(!color[j])
        {
            if(!dfs(j,3-c)) return false;
        }
        else if(color[j] == c) return false;
    }
    return true;
}

int main()
{
    cin>>n>>m;
    memset(h,-1,sizeof h);
    
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        add(a,b),add(b,a);
    }
    
    bool flag = true;
    for(int i=1;i<=n;i++)
    {
        if(!color[i])
        {
            if(!dfs(i,1))
            {
                flag = false;
                break;
            }
        }
    }
    if(flag) puts("Yes");
    else puts("No");
    return 0;
}