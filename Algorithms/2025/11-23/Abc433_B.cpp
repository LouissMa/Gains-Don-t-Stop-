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
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++)
    {
        if(i == 1) 
        {
            cout<<-1<<endl;
            continue;
        }
        for(int j=i-1;j>=1;j--)
        {
            if(a[j] > a[i])
            {
                cout<<j<<endl;
                break;
            }
            if(j == 1)
            {
                cout<<-1<<endl;
                break;
            }
        }
    }
    return 0;
}