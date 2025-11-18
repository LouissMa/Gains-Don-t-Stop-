#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,k;
    cin>>n>>k;
    vector<int> r(n);
    for(int i=0;i<n;i++) cin>>r[i];
    vector<int> a(n);
    auto dfs = [&](auto self,int i,int s) ->void{
        if(i == n)
        {
            if(s % k == 0)
            {
                for(int i=0;i<n;i++)
                {
                    cout<<a[i]<<" \n"[i==n-1];
                }
            }
            return;
        }
        for(a[i] = 1;a[i] <= r[i];a[i]++)
        {
            self(self,i+1,s+a[i]);
        }
    };
    dfs(dfs,0,0);
    return 0;
}