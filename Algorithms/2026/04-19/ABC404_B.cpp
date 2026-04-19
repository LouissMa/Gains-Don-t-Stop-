/*
Problem: Grid Rotation
Contest: AtCoder Beginner Contest 404
URL: https://atcoder.jp/contests/abc404/tasks/abc404_b
Memory Limit: 1024 MB
Time Limit: 2000 ms

Description:
Paste problem statement here
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 110;
int n;
char s[4][N][N],t[N][N];
signed main()
{
    SPEED;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++) cin>>s[0][i][j];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++) cin>>t[i][j];
    }
    for(int i=0;i<3;i++)
    {
        for(int x=0;x < n;x++)
        {
            for(int y=0;y < n;y++) s[i+1][y][n-x-1]=s[i][x][y];
        }
    }
    int ans = 1e9;
    for(int i=0;i<4;i++)
    {
        int sum = i;
        for(int x=0;x<n;x++) for(int y=0;y<n;y++) sum+=(s[i][x][y]!=t[x][y]);
        ans=min(ans,sum);
    }
    cout<<ans<<endl;
    return 0;
}