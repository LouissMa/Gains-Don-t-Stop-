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
    for(int i=1; ; i++)
    {
        int res = n * i;
        if(res % 2 == 0 && res % 5 == 0)
        {
            cout<<i<<endl;
            break;
        }
    }
    return 0;
}