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
    vector<vector<int>> C(n,vector<int>(n));
    for(int i=0;i<n;i++)
    {
        for(int j=i + 1;j<n;j++)
        {
            cin>>C[i][j];
        }    
    }
    for(int i=0;i<n;i++)
    {
        for(int j=i + 1;j<n;j++)
        {
            for(int k = j + 1;k<n;k++)
            {
                if(C[i][j] + C[j][k] < C[i][k])
                {
                    cout<<"Yes"<<endl;
                    return 0;
                }
            }
        }
    }
    cout<<"No"<<endl;
    return 0;
}