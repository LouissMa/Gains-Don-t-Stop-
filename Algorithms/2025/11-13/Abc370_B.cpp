#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin>>n;
    vector<vector<int>> f(n,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            cin>>f[i][j];
            f[i][j] --;
            f[j][i] = f[i][j];
        }
    }
    int x = 0;
    for(int i=0;i<n;i++)
    {
        x = f[x][i];
    }
    cout<<x+1<<endl;
    return 0;
}