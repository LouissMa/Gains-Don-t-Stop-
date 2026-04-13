/*
Problem: Dislike Foods
Contest: Tokio Marine & Nichido Fire Insurance Programming Contest 2025 (AtCoder Beginner Contest 402)
URL: https://atcoder.jp/contests/abc402/tasks/abc402_c
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

const int N = 3e5+10;
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    vector<vector<int>> d(m);
    for(int i=0;i<m;i++)
    {
        int k;
        cin>>k;
        d[i].resize(k);
        for(int j=0;j<k;j++) cin>>d[i][j];
    }
    vector<int> day(n+1,0);
    for(int i=1;i<=n;i++)
    {
        int b;
        cin>>b;
        day[b] = i;
    }
    vector<int> f(n+2,0);
    for(int i=0;i<m;i++)
    {
        int maxx = 0;
        for(int j : d[i])
        {
            if(day[j] > maxx) maxx = day[j];
        }
        f[maxx] ++;
    }
    int ans = 0;
    for(int i=1;i<=n;i++)
    {
        ans += f[i];
        cout<<ans<<endl;
    }
    return 0;
}