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
    set<int> a,b,c;
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        a.insert(x);
        c.insert(x);
    }
    for(int i=0;i<m;i++)
    {
        int x;
        cin>>x;
        b.insert(x);
        c.insert(x);
    }
    if(n == 1)
    {
        cout<<"No\n";
        return 0;
    }
    vector<int> ans(c.begin(),c.end());
    for(int i=0;i<ans.size()-1;i++)
    {
        if(a.count(ans[i]) && a.count(ans[i+1]))
        {
            cout<<"Yes\n";
            return 0;
        }
    }
    cout<<"No\n";
    return 0;
}