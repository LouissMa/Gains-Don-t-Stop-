#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e4 + 10,Max = 1e6 +10;
int n,q,block;
int a[N],cnt[Max],ccnt[N],ans[N],max_fre;

struct Query{
    int l,r,id;
    bool operator < (const Query &t) const{
        if(l / block != t.l / block)
        {
            return l / block < t.l / block;
        }
        if((l/block) & 1) return r < t.r;
        return r > t.r;
    }
}qe[N];

void add(int x)
{
    ccnt[cnt[a[x]]] --;
    cnt[a[x]] ++;
    ccnt[cnt[a[x]]] ++;
    if(cnt[a[x]] > max_fre) max_fre = cnt[a[x]];
}

void del(int x)
{
    ccnt[cnt[a[x]]] --;
    if(cnt[a[x]] == max_fre && ccnt[cnt[a[x]]] == 0) max_fre --;
    cnt[a[x]] --;
    ccnt[cnt[a[x]]] ++;
}
signed main()
{
    SPEED;
    cin>>n>>q;
    block = sqrt(n);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=q;i++)
    {
        cin>>qe[i].l>>qe[i].r;
        qe[i].id = i;
    }
    sort(qe+1,qe+q+1);
    int L = 1,R = 0;
    max_fre = 0;
    for(int i=1;i<=q;i++)
    {
        int l = qe[i].l,r = qe[i].r;
        while(L > l) add(--L);
        while(R < r) add(++R);
        while(L < l) del(L++);
        while(R > r) del(R--);
        ans[qe[i].id] = max_fre;
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
    return 0;
}