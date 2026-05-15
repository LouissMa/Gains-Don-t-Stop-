#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,q;
    cin>>n>>q;
    vector<int> cnt(2001,0);
    int sum = 0;
    int maxx = 0;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        cnt[a] ++;
        sum += a;
        maxx = max(maxx,a);
    }
    for(int i=0;i<q;i++)
    {
        int x;
        cin>>x;
        if(x == 1 || maxx == 0)
        {
            cout<<sum<<endl;
            continue;
        }
        vector<int> ncnt(maxx / x + 1,0);
        int new_sum = 0;
        int new_maxx = 0;
        for(int v = 1;v<=maxx;v++)
        {
            if(cnt[v] > 0)
            {
                int nv = v / x;
                ncnt[nv] += cnt[v];
                new_sum += 1LL * nv * cnt[v];
                if(nv > new_maxx) new_maxx = nv;
            }
        }
        cnt = ncnt;
        maxx = new_maxx;
        sum = new_sum;
        cout<<sum<<endl;
    }
    return 0;
}