#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    vector<int> a(3);
    for(int i=0;i<3;i++) cin>>a[i];
    sort(a.begin(),a.end(),greater<int>());
    if(a[0] - a[2] >= 10)
    {
        cout<<"check again\n";
    }
    else
    {
        cout<<"final "<<a[1]<<"\n";
    }
    return 0;
}