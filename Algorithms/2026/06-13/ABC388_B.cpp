#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 110;
int T[N],L[N],sum[N],org[N];
signed main()
{
    SPEED;
    int n,d;
    cin>>n>>d;
    for(int i=1;i<=n;i++) cin>>T[i]>>L[i];
    for(int i=1;i<=n;i++)
    {
        org[i] = T[i] * L[i];
    }
    for(int i=1;i<=d;i++)
    {
        int ans = 0;
        for(int j=1;j<=n;j++)
        {
            sum[j] = org[j] + i * T[j];
            ans = max(ans,sum[j]);
        }
        cout<<ans<<endl;
    }
    return 0;
}