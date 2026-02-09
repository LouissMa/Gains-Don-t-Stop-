#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
const int N = 1e6 + 10,mod = 1e9 + 7;
int fact[N],infact[N];

int qmi(int a,int k)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res = res * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return res;
}
signed main()
{
    SPEED;
    int n;
    cin>>n;
    fact[0] = infact[0] = 1;
    for(int i=1;i<N;i++)
    {
        fact[i] = fact[i-1] * i % mod;
        infact[i] = infact[i-1] * qmi(i,mod - 2) % mod;
    }
    while(n--)
    {
        int a,b;
        cin>>a>>b;
        cout<<fact[a] * infact[b] % mod * infact[a - b] % mod << "\n";
    }
    return 0;
}