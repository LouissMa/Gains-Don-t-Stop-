#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,k,x;
    cin>>n>>k>>x;
    for(int i=1;i<=n;i++)
    {
        int a;
        cin>>a;
        cout<<a<<" ";
        if(i == k)
        {
            cout<<x<<" ";
        }
    }
    cout<<endl;
    return 0;
}