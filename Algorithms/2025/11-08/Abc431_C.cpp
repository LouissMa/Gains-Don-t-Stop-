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
    vector<int> a(n),b(m);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<m;i++) cin>>b[i];
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int j = 0;
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        while(j < m && a[i] > b[j]) j++;
        if(j < m)
        {
            ans ++;
            j++;
        }
        else break;
    }
    if(ans >= k)
    {
        cout<<"Yes"<<endl;
    }
    else
    {
        cout<<"No"<<endl;
    }
    return 0;
}