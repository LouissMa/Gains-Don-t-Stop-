#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int deg[3] {};
    for(int i=0;i<3;i++)
    {
        for(int j=i+1;j<3;j++)
        {
            char s;
            cin>>s;
            if(s == '<') deg[i]++;
            else deg[j]++;
        }
    }
    for(int i=0;i<3;i++)
    {
        if(deg[i] == 1)
        {
            cout<<char('A' + i)<<endl;
        }
    }
    return 0;
}