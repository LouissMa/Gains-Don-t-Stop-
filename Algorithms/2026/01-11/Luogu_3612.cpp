#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5+10;
int n,m;
int s[N];

int lowbits(int x)
{
    return x & -x;
}
struct node
{
    int c[N];
    void add(int x,int d)
    {
        s[x] += d;
        for(int i=x;i<=n;i+=lowbits(i))
        {
            c[i] += d;
        }
    }
    int sum(int x)
    {
        int ans = 0;
        for(int i=x;i>0;i-=lowbits(i))
        {
            ans += c[i];
        }
        return ans;
    }
    void init()
    {
        memset(c,0,sizeof(c));
        for(int i=1;i<=n;i++)
        {
            for(int j=i-lowbits(i)+1;j<=i;j++)
            {
                c[i] = c[i] + s[j];
            }
        }
    }
}a;
signed main()
{
    SPEED;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>s[i];
    a.init();
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        int l,r;
        cin>>l>>r;
        cout<<a.sum(r)-a.sum(l-1)<<endl;
    }
    return 0;
}