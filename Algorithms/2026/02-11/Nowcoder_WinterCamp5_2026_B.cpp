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
    char c = '/';
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if((i + j) % 2 == 0)
            {
                cout<<'/';
            }
            else cout<<'\\';
        }
        cout<<endl;
    }
    return 0;
}