#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
signed main()
{
    SPEED;
    int n;
    cin>>n;
    vector<string> g(n);
    for(int i=0;i<n;i++) cin>>g[i];
    unordered_set<string> mp;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            string s  ="";
            s += g[i][j];
            mp.insert(s);
            for(int d=0;d < 8;d++)
            {
                string cur = s;
                int nx = i + dx[d];
                int ny = j + dy[d];
                while(nx >= 0 && nx < n && ny >= 0 && ny < n)
                {
                    cur += g[nx][ny];
                    mp.insert(cur);
                    nx += dx[d];
                    ny += dy[d];
                }
            }
        }
    }
    cout<<mp.size()<<endl;
    return 0;
}