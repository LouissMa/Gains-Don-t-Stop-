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
    vector<int> a(n),c(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i]>>c[i];
    }
    vector<int> p(n);
    iota(p.begin(),p.end(),0);
    sort(p.begin(),p.end(),[&](int i,int j){return a[i]>a[j];});
    int min = 1e9+1;
    vector<int> ans;
    for(int i : p)
    {
        if(c[i] < min)
        {
            min = c[i];
            ans.push_back(i+1);
        }
    }
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<"\n";
    for(int i=0;i<ans.size();i++)
    {
        cout<<ans[i]<<" \n"[i==ans.size() - 1];
    }
    return 0;
}