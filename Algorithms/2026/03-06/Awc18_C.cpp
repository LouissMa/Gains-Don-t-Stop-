#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,q;
    cin>>n>>q;
    vector<string> s(n);
    for(int i=0;i<n;i++) cin>>s[i];
    vector<int> t(26,0);
    for(int i=0;i<26;i++) t[i] = i;
    while(q --)
    {
        char a,b;
        cin>>a>>b;
        for(int i=0;i<26;i++)
        {
            if(t[i] == a - 'a') t[i] = b - 'a';
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<s[i].size();j++)
        {
            s[i][j] = t[(s[i][j] - 'a')] + 'a';
        }
        cout<<s[i]<<endl;
    }
    return 0;
}