#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin>>n;
    vector<int> x(n),p(n);
    for(int i=0;i<n;i++)
    {
        cin>>x[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>p[i];
    }
    vector<int> pre(n+1);
    for(int i=0;i<n;i++) pre[i+1] = pre[i] + p[i];
    int q;
    cin>>q;
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        r++;
        int L = lower_bound(x.begin(),x.end(),l) - x.begin();
        int R = lower_bound(x.begin(),x.end(),r) - x.begin();
        cout<<pre[R] - pre[L]<<endl;
    }
    return 0;
}