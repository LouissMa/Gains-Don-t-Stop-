#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

bool is_prime(int x)
{
    if(x < 2) return false;
    for(int i=2;i * i <= x; i++)
    {
        if(x % i == 0) return false;
    }
    return true;
}
signed main()
{
    SPEED;
    int ans = 0;
    for(int i=1; ; i++)
    {
        if(is_prime(i))
        {
            ans ++;
            if(ans == 2025)
            {
                cout<<i<<"\n";
                return 0;
            }
        }
    }
}