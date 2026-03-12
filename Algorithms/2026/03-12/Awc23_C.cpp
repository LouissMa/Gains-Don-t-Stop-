#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2e5 +10;
int T[N],pre[N];
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    pre[0] = 0;
    for(int i=1;i<=n;i++) 
    {
        cin>>T[i];
        pre[i] = pre[i - 1] + T[i];
    }
    for(int i=0;i<m;i++)
    {
        int s,l,r;
        cin>>s>>l>>r;
        int sum = s + pre[r] - pre[l - 1];
        cout<<sum<<endl;
    }
    return 0;
}