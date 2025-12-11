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
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<int> sum(m);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            int x;
            cin>>x;
            sum[j] += x; 
        }
    }
    bool ok = true;
    for(int i=0;i<m;i++)
    {
        if(sum[i] < a[i])
        {
            ok = false;
            break;
        }
    }
    if(ok) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}