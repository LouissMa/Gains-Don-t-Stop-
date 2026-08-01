#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    vector<int> cnt(n + 1, 0);
    map<PII, int> c;
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        if(u > v) swap(u,v);
        cnt[u] ++;
        cnt[v] ++;
        c[{u,v}] ++;
    }
    vector<int> v = cnt;
    sort(v.begin() + 1,v.end());
    int ans = 0;
    int l = 1,r = n;
    while(l < r)
    {
        if(v[l] + v[r] >= m)
        {
            ans += (r - l);
            r--;
        }
        else l++;
    }
    for(auto& p : c)
    {
        int x = p.first.first;
        int y = p.first.second;
        int c = p.second;
        if(cnt[x] + cnt[y] >= m && cnt[x] + cnt[y] - c < m) ans --;
    }
    cout<<ans<<"\n";
    return 0;
}