#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,a;
    cin>>n>>a;
    int lst = -1e9;
    for(int i=0;i<n;i++)
    {
        int t;
        cin>>t;
        lst = max(lst,t) + a;
        cout<<lst<<endl;
    }
}