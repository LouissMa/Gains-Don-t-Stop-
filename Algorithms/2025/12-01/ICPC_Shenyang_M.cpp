#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

int n,a[10],b[10],p[10];
double ans;
struct info
{
    double f[10];
};
info dc(int l,int r)
{
    if(l == r)
    {
        info x;
        for(int i=1;i<=8;i++) x.f[i] = 0;
        x.f[p[l]] = 1;
        return x;
    }
    int mid = (l + r) >> 1;
    return merge(dc(l,mid),dc(mid+1,r));
}

info merge(const info &x,const info &y)
{
    info z;
    for(int i=1;i<=8;i++) z.f[i] = 0;
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            // 计算 i 赢 j 的概率，加到 i 身上
            z.f[i] += x.f[i] * y.f[j] * a[i] / (a[i] + b[j]);
            
            // 计算 j 赢 i 的概率，加到 j 身上
            z.f[j] += x.f[i] * y.f[j] * b[j] / (a[i] + b[j]);
        }
    }
    return z;
}

void work()
{
    ans = max(ans,dc(1,n).f[1]);
}
signed main()
{
    SPEED;
    for(int i=1;i<=8;i++)
    {
        cin>>a[i]>>b[i];
        p[i] = i;
    }
    do work(); while(next_permutation(p+1,p+9));
    printf("%.12lf\n",ans);
}