#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5 + 10;
struct Node{
    int v,id,c;
    vector<int> t;
}a[N];

int b[N];
bool com(Node a,Node b)
{
    if(a.v != b.v) return a.v > b.v;
    return a.id < b.id; 
}
signed main()
{
    SPEED;
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].v;
        cin>>a[i].c;
        a[i].id = i;
        for(int j=1;j<=a[i].c;j++)
        {
            int x;
            cin>>x;
            a[i].t.push_back(x);
        }
    }
    sort(a + 1,a + n + 1,com);
    for(int i=1;i<=k;i++)
    {
        if(a[i].c == 0) continue;
        for(int j=0;j<a[i].t.size();j++)
        {
            b[a[i].t[j]] ++;
        }
    }
    int ans = 0;
    for(int i=1;i<=m;i++)
    {
        if(b[i] == k) ans ++;
    }
    cout<<ans<<"\n";
    return 0;
}