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
    vector<int> p(m);
    for(int i=0;i<m;i++) cin>>p[i];
    for(int i=0;i<n;i++)
    {
        int k;
        cin>>k;
        int idx = 0;
        int grade = 0;
        vector<int> c(k);
        for(int j=0;j<k;j++)
        {
            cin>>c[j];
            c[j] --;
        }
        sort(c.begin(), c.end());
        for(int j=0;j<k;j++)
        {
            if(p[c[j]] > grade)
            {
                grade = p[c[j]];
                idx = c[j] + 1;
            }
        }
        cout<<idx<<"\n";
    }
    return 0;
}