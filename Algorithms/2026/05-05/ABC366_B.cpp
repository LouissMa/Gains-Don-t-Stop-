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
    vector<string> s(n);
    int m = 0;
    for(int i=0;i<n;i++)
    {
        cin>>s[i];
        m = max(m, (int)s[i].size());
    }
    vector<string> T(m);
    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<m;j++)
        {
            T[j] += (j<s[i].size() ? s[i][j] : '*');
        }
    }
    for(int i=0;i<m;i++)
    {
        while(T[i].back() == '*') T[i].pop_back();
        cout<<T[i]<<'\n';
    }
    return 0;
}