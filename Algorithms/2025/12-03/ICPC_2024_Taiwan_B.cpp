#include <bits/stdc++.h>
using namespace std;

using ui = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(l);i>=(r);--i)
#define repn(i,n)  for(int i=0;i<(n);++i)
#define sizc(x) ((int)x.size())
#define allc(x) x.begin(),x.end()
#define fir first
#define sec second

constexpr int N = 3e5+5;

int n;
ll a[N];
ll sa[N],sb[N];
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    rep(i,1,n)cin>>a[i];
    rep(i,1,n){
        sa[i]=sa[i-1]+a[i];
        sb[i]=sb[i-1]-a[i];
        if(a[i]<0)sb[i]-=2*a[i];
    }
    rep(i,1,n)sb[i]=max(sb[i],sb[i-1]);
    ll tmp=0,ans=0;
    per(i,n,1){
        ans=max(ans,tmp+sa[i]+sb[i-1]);
        if(a[i]<0)tmp-=2*a[i];
    }
    ans=max(ans,tmp);
    cout<<ans+sa[n]<<'\n';
}