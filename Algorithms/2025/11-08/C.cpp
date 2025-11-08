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
    int maxx1 = -1e18,maxx2 = -1e18;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        maxx1 = max(maxx1,a);
    }
    for(int i=0;i<n;i++)
    {
        int b;
        cin>>b;
        maxx2 = max(maxx2,b);
    }
    cout<<maxx1+maxx2<<endl;
    return 0;
}