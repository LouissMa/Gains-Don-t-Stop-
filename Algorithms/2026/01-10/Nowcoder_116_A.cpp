#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    vector<int> a(3);
    int x;
    for(int i=0;i<3;i++)
    {
        cin>>a[i];
    }
    cin>>x;
    x--;
    int c = a[x];
    sort(a.begin(), a.end());
    if(a[2] == c)
    {
        cout<<"Yes\n";
    }
    else
    {
        cout<<"No\n";
    }
    return 0;
}