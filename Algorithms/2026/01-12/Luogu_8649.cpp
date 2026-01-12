#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
const int N = 1e5 + 5;
int n,k;
int a[N],pre[N];
vector<vector<int>> y(N);
signed main()
{
    SPEED;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    pre[0] = 0;
    y[0].push_back(0);
    for(int i=1;i<=n;i++) pre[i] = pre[i-1] + a[i];
    for(int i=1;i<=n;i++)
    {
        int x = pre[i] % k;
        y[x].push_back(i);
    }
    int ans = 0;
    for(auto x : y)
    {
        int num = x.size();
        ans += num * (num - 1) / 2;
    }
    cout<<ans<<"\n";
    return 0;
}