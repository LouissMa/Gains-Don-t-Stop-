#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    vector<int> c(m);
    for(int i=0;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        a --;b --;
        c[a] --;
        c[b] ++;
    }
    for(int i=0;i<m;i++) cout<<c[i]<<"\n";
    return 0;
}