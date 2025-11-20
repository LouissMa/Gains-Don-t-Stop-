#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define ll long long
using namespace std;
struct node
{
    ll w,h;
    node(){w=0,h=0;}
    node(ll w,ll h):w(w),h(h){}
    bool operator <(const node &a)const{return a.w==w?h>a.h:w>a.w;}
};
ll ans;
priority_queue<node>q;
int main()
{
    ll n,k;ans=0;scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)
    {
        ll w;scanf("%lld",&w);
        q.push(node(w,1));
    }
    while((q.size()-1)%(k-1)!=0)q.push(node(0,1));
    while(q.size()>=k)
    {
        ll h=-1;ll w=0;
        for(int i=1;i<=k;++i)
        {
            node t=q.top();q.pop();
            h=max(h,t.h);
            w+=t.w;
        }
        ans+=w;
        q.push(node(w,h+1));
    }
    printf("%lld\n%lld\n",ans,q.top().h-1);
    return 0;
}
