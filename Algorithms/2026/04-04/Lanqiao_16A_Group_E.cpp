#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int mod = 1000000007;
const int N = 5e5 + 10;
int fac[N],infac[N];

int qmi(int a,int k,int p)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}
signed main()
{
    SPEED;
    fac[0] = infac[0] = 1;
    for(int i=1;i<N;i++)
    {
        fac[i] = fac[i - 1] * i % mod;
        infac[i] = infac[i - 1] * qmi(i,mod - 2,mod) % mod;
    }
    int n;
    cin>>n;
    map<int,int> mp;
    for(int i=1;i<=n;i++)
    {
        int t;
        cin>>t;
        mp[t] ++;
    }
    int tar = n - 2;
    int x = fac[tar];
    for(auto [k,v] : mp)
    {
        x = x * infac[v] % mod;
    }
    int ans = 0;
    for(auto [k,v] : mp)
    {
        if(tar % k != 0 || mp.count(tar / k) == 0 || (tar == k * k && mp[k] < 2)) continue;
        int tot = x;
        if(tar == k * k)
        {
            tot = tot * fac[v] % mod * infac[v - 2] % mod;
        }
        else
        {
            tot = tot * fac[v] % mod * fac[mp[tar / k]] % mod * infac[v - 1] % mod * infac[mp[tar / k] - 1] % mod;
        }
        ans = (ans + tot) % mod;
    }
    cout<<ans<<endl;
    return 0;
}