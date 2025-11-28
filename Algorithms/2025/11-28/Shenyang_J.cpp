#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    vector<vector<int>> v(n);
    while(m--)
    {
        int op;
        cin>>op;
        if(op == 1)
        {
            int i,x;
            cin>>i>>x;
            i--;
            v[i].push_back(x);
        }
        else
        {
            int i1,j1,i2,j2;
            cin>>i1>>j1>>i2>>j2;
            i1--;
            j1--;
            i2--;
            j2--;
            int c = v[i1][j1];
            int d = v[i2][j2];
            v[i1][j1] = d;
            v[i2][j2] = c;
        }
    }
    for(int i=0;i<n;i++)
    {
        cout<<v[i].size();
        for(int j=0;j<v[i].size();j++)
        {
            cout<<" "<<v[i][j];
        }
        cout<<"\n";
    }
    return 0;
}