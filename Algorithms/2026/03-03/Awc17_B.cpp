#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2e5 +10;
int a[N];
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) 
    {
        int b;
        cin>>b;
        if(b - 1 >= 1) a[b - 1] ++;
        if(b + 1 <= n) a[b + 1] ++;
        a[b] ++;
    }
    for(int i=1;i<=n;i++) cout<<a[i]<<" \n"[i == n];
    return 0;
}