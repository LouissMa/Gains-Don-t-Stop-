#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int r,g,b;
    cin>>r>>g>>b;
    string s;
    cin>>s;
    int minn = 1010;
    if(s == "Red")
    {
        minn = min(g,b);
    }
    else if(s == "Green") minn = min(r,b);
    else minn = min(r,g);
    cout<<minn<<endl;
    return 0;
}