#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int a,b;
    cin>>a>>b;
    int sum = 6;
    if(a == b)
    {
        cout<<-1<<endl;
    }
    else
    {
        cout<<sum - (a+b)<<endl;
    }
    return 0;
}