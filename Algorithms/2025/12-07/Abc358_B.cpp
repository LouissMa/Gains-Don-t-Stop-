#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,a;
    cin>>n>>a;
    bool ok = false;
    int con = 0;
    vector<int> t(n);
    for(int i=0;i<n;i++) cin>>t[i];
    for(int i=0;i<n;i++)
    {
        int x = t[i];
        if(ok)
        {
            x += con;
            x += a;
            if(x >= t[i+1] && i+1 < n)
            {
                ok = true;
                con = x - t[i+1];
            }
            else ok = false;
        }
        else
        {
            x += a;
            if(x >= t[i+1] && i+1 < n)
            {
                ok = true;
                con = x - t[i+1];
            }
            else ok = false;
        }
        cout<<x<<endl;
    }
}