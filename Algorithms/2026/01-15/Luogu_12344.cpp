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
    char ans = *max_element(s.begin(), s.end());
    int cnt = 0;
    for(auto i:s)
    {
        if(i == ans) cnt++;
    }
    cout<<string(cnt,ans)<<endl;
    return 0;
}