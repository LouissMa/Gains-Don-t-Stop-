#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int a[3];
    cin>>a[0]>>a[1]>>a[2];
    sort(a,a+3);
    if(a[0] == a[1] && a[1] == a[2])
    {
        cout<<"Yes\n";
        return 0;
    } 
    if(a[0] + a[1] == a[2])
    {
        cout<<"Yes\n";
        return 0;
    }
    cout<<"No\n";
    return 0;
}