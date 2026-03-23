#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2e5 + 10;
int L[N];
signed main()
{
    SPEED;
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        int l,r;
        cin>>l>>r;
        L[l] ++;
        L[r + 1] --;
    }
    for(int i=1;i<=n;i++) L[i] += L[i - 1];
    int ans = 0;
    int j = 0;
    for(int i=1;i<=n;i++)
    {
        if(L[i]>=k && j == 0)
        {
            j = i;
            continue;
        }
        if(L[i] >= k && j != 0)
        {
            j ++;
            continue;
        }
        ans += i - j;
        j = 0;
    }
    cout<<ans<<endl;
    return 0;
}