#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 110;
int a[N][N],pre[N][N];
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
            if(a[i][j] == 0) a[i][j] = -1;
            pre[i][j] = a[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
        }
    }
    int ans = 0;
    for(int r1 = 1;r1 <= n;r1++)
    {
        for(int r2 = r1;r2 <= n;r2++)
        {
            for(int c1 = 1;c1 <= m;c1++)
            {
                for(int c2 = c1;c2 <= m;c2++)
                {
                    int sum = pre[r2][c2] - pre[r1-1][c2] - pre[r2][c1-1] + pre[r1-1][c1-1];
                    if(sum > 0) ans ++;
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}