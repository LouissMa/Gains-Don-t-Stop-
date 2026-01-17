#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
int vis[10000001];
signed main()
{
    SPEED;
    int n;
    cin>>n;
    for(int i=1;i * i <= n;i++)
    {
        for(int j=i+1;i* i+ j * j <= n;j++)
        {
            vis[i* i+ j * j] ++;
        }
    }
    int cnt = 0;
    for(int i=1;i<=n;i++)
    {
        if(vis[i] == 1) cnt++;
    }
    cout<<cnt<<endl;
    for(int i=1;i<=n;i++)
    {
        if(vis[i] == 1) cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}