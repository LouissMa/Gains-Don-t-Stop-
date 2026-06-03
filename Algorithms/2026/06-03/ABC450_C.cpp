#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int dx[] = {1,0,-1,0};
const int dy[] = {0,1,0,-1};
signed main()
{
    SPEED;
    int h,w;
    cin>>h>>w;
    vector<string> s(h);
    for(int i=0;i<h;i++) cin>>s[i];
    vector<vector<int>> vis(h,vector<int>(w));
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
            if(s[i][j] == '#') vis[i][j] = 1;
    }
    int ans = 0;
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            if(vis[i][j]) continue;
            queue<array<int,2>> q;
            q.push({i,j});
            bool ok = false;
            vis[i][j] = 1;
            while(!q.empty())
            {
                const auto [x,y] = q.front();
                q.pop();
                if(x == 0 || x == h - 1 || y == 0 || y == w - 1)
                {
                    ok = true;
                }
                for(int k=0;k<4;k++)
                {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if(0 <= nx && nx < h && 0 <= ny && ny < w && !vis[nx][ny])
                    {
                        vis[nx][ny] = 1;
                        q.push({nx,ny});
                    }
                }
            }
            if(!ok) ans ++;
        }
    }
    cout<<ans<<"\n";
    return 0;
}