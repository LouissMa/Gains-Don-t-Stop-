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
    for(int i=1;i<=m;i++)
    {
        int n,k;
        cin>>n>>k;
        int x = (1 << (n - 1)) + k - 1;
        int cnt = 0;
        while(x > 1)
        {
            if(x & 1) cnt ++;
            x >>= 1;
        }
        if(cnt & 1) cout<<"BLACK"<<endl;
        else cout<<"RED"<<endl;
    }
    return 0;
}