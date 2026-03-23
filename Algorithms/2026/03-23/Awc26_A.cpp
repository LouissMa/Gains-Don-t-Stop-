#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,k;
    cin>>n>>k;
    vector<int> a(n + 1);
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=k;i<=n;i+=k)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;
}