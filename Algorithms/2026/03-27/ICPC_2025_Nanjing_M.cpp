#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = (1 << 20) + 5, MOD = 998244353;
int n, a[N], b[N], fc[N], invfc[N];
int lim = 1, r[N], g[N];

void W(int &x, int y)
{
    x += y;
    if (x >= MOD)
        x -= MOD;
}
void W(int &x, ll y) { x = (x + y) % MOD; }
int W1(int x, int y)
{
    x += y;
    return x < MOD ? x : x - MOD;
}

int qpow(int x,int y)
{
    int t = 1;
    for(;y;y/=2,x = (ll)x * x % MOD)
    {
        if(y & 1)
        {
            t = (ll)t * x % MOD;
        }
    }
    return t;
}

void init(int n)
{
    
}
int main()
{
    SPEED;
    
}