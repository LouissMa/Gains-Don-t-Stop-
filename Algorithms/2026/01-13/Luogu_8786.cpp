#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 210;
int f[N][N][N];
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    f[0][0][2] = 1;
    for(int i=0;i<n + m;i++)
    {
        for(int j=0;j<m;j++)
        {
            for(int k=0;k<=m;k++)
            {
                if(f[i][j][k])
                {
                    if(k > 0) f[i + 1][j + 1][k - 1] = (f[i + 1][j + 1][k - 1] + f[i][j][k]) % 1000000007;
                    if(k <= 50)
                    {
                        f[i + 1][j][k * 2] = (f[i+1][j][k*2] + f[i][j][k]) % 1000000007;
                    }
                }
            }
        }
    }
    cout<<f[n + m][m][0]<<endl;
    return 0;
}