#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int m;
    cin>>m;
    vector<int> a;
    int t = 0;
    while(m > 0)
    {
        for(int i=0;i<m%3;i++) a.push_back(t);
        t++;
        m /= 3;
    }
    cout<<a.size()<<endl;
    for(auto i : a) cout<<i<<" \n"[i==a.size() - 1];
    return 0;
}