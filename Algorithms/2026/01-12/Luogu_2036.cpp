#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 50;
int pre[N],sum[N];
int s[N],b[N];
signed main()
{
    SPEED;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>s[i]>>b[i];
    }
    int ans = 1e18;
    for(int mark = 1;mark < (1 << n);mark++)
    {
        int sour = 1;
        int bitt = 0;
        for(int i=0;i<n;i++)
        {
            if(mark & (1 << i))
            {
                sour *= s[i];
                bitt += b[i];
            }
        }
        ans = min(ans,abs(sour - bitt));
    }
    cout<<ans<<endl;
    return 0;
}