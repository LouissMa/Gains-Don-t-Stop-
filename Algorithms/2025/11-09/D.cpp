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
    vector<int> h(n);
    for(int i=0;i<n;i++) cin>>h[i];
    vector<int> stk;
    vector<int> ans(n);
    for(int i=n-1;i>=0;i--)
    {
        ans[i] = stk.size();
        while(!stk.empty() && h[stk.back()] < h[i])
        {
            stk.pop_back();
        }
        stk.push_back(i);
    }
    for(int i=0;i<n;i++)
    {
        cout<<ans[i]<<" \n"[i==n-1];
    }
    return 0;
}