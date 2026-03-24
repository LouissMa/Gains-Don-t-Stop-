#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,k;
    cin>>n>>k;  
    int sum1 = 0,sum2 = 0;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        if(sum1 + a <= k) sum1 += a;
        else sum2 += a;
    }
    if(sum1 > sum2) cout<<"Takahashi\n";
    else if(sum1 == sum2) cout<<"Draw\n";
    else cout<<"Aoki\n";
    return 0;
}