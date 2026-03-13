#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2e5 + 10;
int l[N],r[N];
signed main()
{
    SPEED;
    int n,w,k;
    cin>>n>>w>>k;
    for(int i=1;i<=k;i++)
    {
        int L;
        cin>>L;
        l[L] ++;
        l[L + w] --;
    }
    for(int i=1;i<=n;i++) l[i] += l[i - 1];
    for(int i=1;i<=n;i++)
    {
        cout<<l[i]<<" \n"[i == n];
    }
    return 0;
}