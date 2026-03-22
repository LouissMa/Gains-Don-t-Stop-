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
    for(int i=n;i>=1;i--)
    {
        if(i == 1) cout<<i;
        else cout<<i<<",";
    }
    cout<<endl;
    return 0;
}