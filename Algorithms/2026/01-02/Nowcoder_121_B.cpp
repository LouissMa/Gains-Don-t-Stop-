#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,t;
    cin>>n>>t;
    int sum = 0;
    int ans = 0;
    vector<PII> v(n);
    for(int i=0;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        v[i] = {a,b};
        sum += a;
    }
    if(sum >= t)
    {
        cout<<0<<"\n";
        return 0;
    }
    int need = t - sum;
    sort(v.begin(),v.end(),[](PII a,PII b){
        return a.first > b.first;
    });
    for(int i=0;i<n;i++)
    {
        if(v[i].second == 0 || v[i].first == 0) continue;
        int a = v[i].first;
        int b = v[i].second;
        int maxx = a * b;
        if(need <= maxx)
        {
            int cnt = (need + a - 1) / a;
            ans += cnt;
            need = 0;
            break;
        }
        else
        {
            ans += b;
            need -= maxx;
        }
    }
    if(need > 0) cout<<-1<<"\n";
    else cout<<ans<<"\n";
    return 0;
}