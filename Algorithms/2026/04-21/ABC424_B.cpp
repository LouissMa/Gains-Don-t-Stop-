#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m,k;
    cin>>n>>m>>k;
    vector<vector<int>> v(n+1);
    while(k--)
    {
        int a,b;
        cin>>a>>b;
        v[a].push_back(b);
        if(v[a].size() == m)
        {
            cout<<a<<" ";
        }
    }
    cout<<"\n";
    return 0;
}