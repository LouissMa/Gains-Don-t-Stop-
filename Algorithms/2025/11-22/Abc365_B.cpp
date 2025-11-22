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
    vector<PII> v(n);
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        v[i] = {x, i};
    }
    sort(v.begin(),v.end());
    cout<<v[n-2].second + 1<<endl;
    return 0;
}