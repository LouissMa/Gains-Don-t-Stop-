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
    int minn = 1e19;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        minn = min(minn,a);
        cout<<minn<<" ";
    }
    cout<<endl;
    return 0;
}