#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m,t;
    cin>>n>>m>>t;
    vector<int> a(n);
    int diff = 0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        if(a[i] < t) diff += t - a[i];
    }
    if(diff == 0)
    {
        cout<<0<<endl;
        return 0;
    }
    if(diff <= m)
    {
        cout<<diff<<endl;
    }
    else cout<<-1<<endl;
    return 0;

}