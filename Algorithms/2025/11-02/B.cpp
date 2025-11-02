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
    vector<string> s(n);
    for(int i=0;i<n;i++)
    {
        cin>>s[i];
    }
    set<vector<string>> st;
    for(int i=0;i<n-m;i++)
    {
        for(int j=0;j<=n-m;j++)
        {
            vector<string> p(m);
            for(int r=0;r<m;r++)
            {
                p[r] = s[i+r].substr(j,m);
            }
            st.insert(p);
        }
    }
    cout<<st.size()<<endl;
    return 0;
}