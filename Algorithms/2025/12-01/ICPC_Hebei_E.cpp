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
    map<string,string> mp;
    for(int i=0;i<n;i++)
    {
        string a,b;
        cin>>a>>b;
        mp[a] = b;
    }
    while(m--)
    {
        string a;
        cin>>a;
        if(mp.count(a)) cout<<mp[a]<<endl;
        else cout<<"NULL"<<endl;
    }
    return 0;
}