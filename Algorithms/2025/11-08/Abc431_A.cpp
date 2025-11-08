#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int h,w;
    cin>>h>>w;
    if(h <= w)
    {
        cout<<0<<"\n";
    }
    else
    {
        cout<<h-w<<"\n";
    }
    return 0;
}