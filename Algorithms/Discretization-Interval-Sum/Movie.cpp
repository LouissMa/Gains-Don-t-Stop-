#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 6e5 + 10;
int n,m;
int a[N],b[N],c[N];
vector<int> alls;
int cnt[N];
int find(int x)
{
    int l = 0,r = alls.size() - 1;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1;
}
signed main()
{
    SPEED;
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        alls.push_back(a[i]);
    }
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>b[i];
        alls.push_back(b[i]);
    }
    for(int i=1;i<=m;i++)
    {
        cin>>c[i];
        alls.push_back(c[i]);
    }
    sort(alls.begin(),alls.end());
    alls.erase(unique(alls.begin(),alls.end()),alls.end());
    for(int i=1;i<=n;i++)
    {
        int idx = find(a[i]);
        cnt[idx] ++;
    }
    int maxx1 = -1,maxx2 = -1;
    int res = 1;
    for(int i=1;i<=m;i++)
    {
        int ad_idx = find(b[i]);
        int sub_idx = find(c[i]);
        if(cnt[ad_idx] > maxx1)
        {
            maxx1 = cnt[ad_idx];
            res = i;
            maxx2 = cnt[sub_idx];
        }
        else if(maxx1 == cnt[ad_idx] && cnt[sub_idx] > maxx2)
        {
            res = i;
            maxx2 = cnt[sub_idx];
        }
    }
    cout<<res<<"\n";
    return 0;
}