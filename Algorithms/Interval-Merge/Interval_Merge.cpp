#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

vector<PII> segs;

void merge(vector<PII> &segs)
{
    vector<PII> res;
    sort(segs.begin(),segs.end());
    int st = -2e9,ed = -2e9;
    for(auto seg : segs)
    {
        int l = seg.first;
        int r = seg.second;
        if(ed < l)
        {
            if(st != -2e9) res.push_back({st,ed});
            st = l;
            ed = r;
        }
        else
        {
            ed = max(ed,r);
        }
    }
    if(st != -2e9)
    {
        res.push_back({st,ed});
    }
    segs = res;
}
signed main()
{
    SPEED;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int l,r;
        cin>>l>>r;
        segs.push_back({l,r});
    }
    merge(segs);
    cout<<segs.size()<<"\n";
    return 0;
}