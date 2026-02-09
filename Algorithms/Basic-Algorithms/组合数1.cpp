#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2010,mod = 1e9 + 7;
int c[N][N];

void init()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if(j == 0) c[i][j] = 1;
            else c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
        }
    }
}
signed main()
{
    SPEED;
    int n;
    cin>>n;
    init();
    while(n --)
    {
        int a,b;
        cin>>a>>b;
        cout<<c[a][b]<<endl;
    }
    return 0;
}