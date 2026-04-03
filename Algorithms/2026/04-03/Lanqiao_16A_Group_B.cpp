#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 10;
int a[N][N];
bool st[N][N];

void dfs(int i,int j)
{
    if(i > 6)
    {
        for(int x = 1; x <= 6; x ++)
        {
            int c1 = 0,c2 = 0;
            for(int y = 1; y <= 6; y ++)
            {
                if(a[x][y] == 1) c1 ++;
                else c2 ++;
            }
            if(c1 != c2) return;
        }
        for(int x = 1; x <= 6; x ++)
        {
            int c1 = 0,c2 = 0;
            for(int y = 1; y <= 6; y ++)
            {
                if(a[y][x] == 1) c1 ++;
                else c2 ++;
            }
            if(c1 != c2) return;
        }
         for (int x = 1; x <= 6; x ++){
            for (int y = 1; y <= 6; y ++) {
                if (x <= 4 && a[x][y] == a[x + 1][y] && a[x][y] == a[x + 2][y] || y <= 4 && a[x][y] == a[x][y + 1] && a[x][y] == a[x][y + 2])
                    return;
            }
        }
        set<string> s;
        for(int t = 1; t <= 6; t++)
        {
            string str;
            for(int x = 1; x <= 6;x ++)
            {
                str += a[t][x] + '0';
            }
            s.insert(str);
        }
        if(s.size() < 6) return;
        s.clear();
        for(int t = 1; t <= 6; t++)
        {
            string str;
            for(int x = 1; x <= 6;x ++)
            {
                str += a[x][t] + '0';
            }
            s.insert(str);
        }
        if(s.size() < 6) return;
        for(int x = 1; x <= 6; x ++)
        {
            for(int y = 1; y <= 6; y ++)
            {
                cout<<a[x][y] - 1;
            }
        }
        cout<<endl;
        exit(0);
    }
    int x = i,y = j;
    while(st[x][y] || a[x][y])
    {
        y ++;
        if(y > 6)
        {
            y = 1;
            x ++;
        }
    }
    a[x][y] = 1;
    dfs(x,y);
    a[x][y] = 2;
    dfs(x,y);
    a[x][y] = 0;
}
signed main()
{
    SPEED;
    a[1][1] = a[5][3] = a[5][6] = a[6][5] = 2;
    a[1][2] = a[1][4] = a[2][4] = a[3][5] = a[3][6] = a[6][2] = 1;
    st[1][1] = st[5][3] = st[5][6] = st[6][5] = st[1][2] = st[1][4] = st[2][4] = st[3][5] = st[3][6] = st[6][2] = true;
    dfs(1,3);
    return 0;
}