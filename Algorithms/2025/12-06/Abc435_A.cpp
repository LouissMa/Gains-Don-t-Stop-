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
    int sum = 0;
    for(int i=1;i<=n;i++) sum += i;
    cout<<sum<<endl;
    return 0;
}