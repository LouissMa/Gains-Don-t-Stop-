#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e4 +10;
PII pos[N];
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>pos[i].first>>pos[i].second;
    for(int i=1;i<=m;i++)
    {
        int x,y,r;
        cin>>x>>y>>r;
        int cnt = 0;
        int r2 = r * r;
        for(int j=1;j<=n;j++)
        {
            int dx = pos[j].first - x;
            int dy = pos[j].second - y;
            if(dx * dx + dy * dy <= r2) cnt ++;
        }
        cout<<cnt<<endl;
    }
    return 0;
}