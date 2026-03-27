#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

void merge(vector<PII> &segs)
{
    vector<PII> res;
    sort(segs.begin(),segs.end());
    int st = -2e9,ed = -2e9;
    for(auto segs : segs)
    {
        if(segs.first > ed)
        {
            if(st != -2e9) res.push_back({st,ed});
            st = segs.first,ed = segs.second;
        }
        else
        {
            ed = max(ed,segs.second);
        }
    }
    if(st != -2e9) res.push_back({st,ed});
    segs = res;
}
signed main()
{
    SPEED;
    int n;
    cin>>n;
    vector<PII> segs;
    for(int i=1;i<=n;i++)
    {
        int l,r;
        cin>>l>>r;
        segs.push_back({l,r});
    }
    merge(segs);
    cout<<segs.size()<<endl;
    return 0;
}