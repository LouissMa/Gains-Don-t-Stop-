#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

constexpr char RPS[] = "RPS";
constexpr int inf = 1E9;
signed main()
{
    SPEED;
    int n;
    cin>>n;
    string s;
    cin>>s;
    vector<int> a(n);
    for(int i=0;i<n;i++)
    {
        a[i] = string(RPS).find(s[i]);
    }
    array<int,3> dp {};
    for(int i=0;i<n;i++)
    {
        array<int, 3> ndp {-inf, -inf, -inf};
        for(int x=0;x < 3;x++){
            for(int y=0;y < 3;y++)
            {
                if ((y + 1) % 3 == a[i] || x == y) 
                {
                    continue;
                }
                ndp[y] = std::max(ndp[y], dp[x] + (y == (a[i] + 1) % 3));
            }
        }
        dp = ndp;
    }
    int ans = *max_element(dp.begin(), dp.end());
    cout<<ans<<"\n";
}