#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 3e5+10;
int a[N],s[N];
vector<PII> add,q;
vector<int> alls;

int find(int x)
{
    int l = 0,r = alls.size()-1;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r+1;
}
signed main()
{
    SPEED;
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        int x,c;
        cin>>x>>c;
        add.push_back({x,c});
        alls.push_back(x);
    }
    for(int i=0;i<m;i++)
    {
        int l, r;
        cin>>l>>r;
        q.push_back({l,r});
        alls.push_back(l);
        alls.push_back(r);
    }
    sort(alls.begin(),alls.end());
    alls.erase(unique(alls.begin(),alls.end()),alls.end());
    for(auto tem : add)
    {
        int x = find(tem.first);
        a[x] += tem.second;
    }
    for(int i=1;i<=alls.size();i++)
    {
        s[i] = s[i-1] + a[i];
    }
    for(auto tem : q)
    {
        int l = find(tem.first);
        int r = find(tem.second);
        cout<<s[r] - s[l-1]<<endl;
    }
    return 0;
}