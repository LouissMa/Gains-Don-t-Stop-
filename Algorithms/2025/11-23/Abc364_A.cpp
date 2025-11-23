#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin >> n;
    vector<string> s(n);
    bool ok = true;
    for(int i=0;i<n;i++) cin>>s[i];
    for(int i=1;i<n;i++) 
    {
        if(s[i] == "sweet" && s[i-1] == "sweet")
        {
            if(i != n-1)
            {
                ok = false;
                break;
            }
            else 
            {
                ok = true;
            }
        }
    }
    if(ok) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
}