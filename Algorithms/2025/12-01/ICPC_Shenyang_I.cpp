#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1010;
int cnt[N];
int vis[N][N];
signed main()
{
    SPEED;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        bool ok = 0;
        if(!vis[a][b])
        {
            vis[a][b] = 1;
            if(c < 240) ok = 1;
            else ok = cnt[a] < 3;
            cnt[a]++;
        }
        if(ok) cout<<b<<endl;
        else cout<<0<<endl;
    }
    return 0;
}