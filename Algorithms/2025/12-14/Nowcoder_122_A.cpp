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
    for(int i=1;i<=13;i++)
    {
        if(i == 1)
        {
            cout<<"A"<<" ";
        }
        else
        {
            if(i > n) break;
            char w = 'A' + i - 1;
            cout<<w<<" ";
        }
    }
    cout<<endl;
    return 0;
}