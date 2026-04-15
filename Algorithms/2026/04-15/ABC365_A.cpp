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
    if(n %4 != 0) cout<<"365\n";
    else if(n % 100 != 0 && n % 4 == 0) cout<<"366\n";
    else if(n % 400 != 0 && n % 100 == 0) cout<<"365\n";
    else cout<<"366\n";
    return 0;
}