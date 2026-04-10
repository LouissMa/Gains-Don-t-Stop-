#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 55;
int d[][2] = {-1, 0, -1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1, -1, -1};
bool st[N][N];
bool ch[N][N][N][N];
int s[N][N];
bool fg = 0;
int n,k;
void dfs(int x,int y,string path)
{
    if(x == n - 1 && y == n-1 || fg)
    {
        if(path.size() == n * n - 1)
        {
            cout<<path<<endl;
            fg = 1;
            exit(0);
        }
        return;
    }
    st[x][y] = true;
    for(int i=0;i<8;i++)
    {
        int a = x + d[i][0], b = y + d[i][1];
        if(a < 0 || a >= n || b < 0 || b >= n) continue;
        if(st[a][b] || s[a][b] != (s[x][y] + 1) % k) continue;
        if (i % 2 && (ch[x][b][a][y] || ch[a][y][x][b])) continue;
        ch[x][y][a][b] = 1;
        dfs(a,b,path + to_string(i));
        ch[x][y][a][b] = 0;
    }
    st[x][y] = 0;
}
signed main()
{
    SPEED;
    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++) cin>>s[i][j];
    }
    dfs(0,0,"");
    if(!fg) cout<<-1<<endl;
    return 0;
}