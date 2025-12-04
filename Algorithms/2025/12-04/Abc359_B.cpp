#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin >> n;
    vector<int> a(2 * n);
    for(int i = 0; i < 2 * n; i ++)
    {
        cin>>a[i];
    }
    int ans = 0;
    for(int i=0;i<2*n;i++)
    {
        int j = i+2;
        if(j < 2 * n && a[i] == a[j]) ans++;
    }
    cout<<ans<<endl;
    return 0;
}