/*
Problem: Problem Title
Contest: Contest Name
URL: URL
Memory Limit: 1024 MB
Time Limit: 2000 ms

Description:
Paste problem statement here
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

const int dx[] = {2,2,-2,-2,1,-1,1,-1};
const int dy[] = {1,-1,1,-1,2,2,-2,-2};
const int dx1[] = {1, 1, -1, -1, 0, 0, 0, 0};
const int dy1[] = {0, 0, 0, 0, 1, 1, -1, -1};
void solve() 
{
    int x,y,x1,y1;
    cin>>x>>y>>x1>>y1;
    for(int i=0;i<8;i++)
    {
        int tx = x + dx[i];
        int ty = y + dy[i];
        int tx1 = x + dx1[i];
        int ty1 = y + dy1[i];
        if(tx >= 1 && tx <= 9 && ty >= 1 && ty <= 10 && (x1 != tx1 || y1 != ty1))
        {
            if ((x1 != tx && y1 != ty) || (x1 == tx && y1 == ty))
            {
                puts("NO");
                return;
            }
        }
    }
    puts("YES");
}

signed main() 
{
    SPEED;
    int t = 1;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}