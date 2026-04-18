#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    string s;
    cin>>s;
    int n = s.size();
    string ans = "";
    for(int i=0;i<n;i++)
    {
        if(s[i] != 'D') ans += s[i];
        else 
        {
            if(ans.size() != 0)
                ans.pop_back();
        }
    }
    if(ans.size() == 0) cout<<"!!!!\n";
    else cout<<ans<<endl;
    return 0;
}