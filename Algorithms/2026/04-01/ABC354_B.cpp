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
    int t = 0;
    vector<string> s(n);
    for(int i=0;i<n;i++)
    {
        cin>>s[i];
        int c;
        cin>>c;
        t += c;
    }
    sort(s.begin(),s.end());
    cout<<s[t % n]<<"\n";
    return 0;
}