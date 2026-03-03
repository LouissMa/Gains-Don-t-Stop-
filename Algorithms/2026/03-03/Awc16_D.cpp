#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

int main()
{
    int n,q;
    ll k;
    cin >> n >> k >> q;

    vector<ll> asum(n+1,0);
    for(int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        asum[i+1] = asum[i] + a;
    }

    vector<ll> fsum(n+1,0);
    for(int i = 1; i <= n; i++)
    {
        ll sum = k + asum[i-1];
        auto it = upper_bound(asum.begin(),asum.end(),sum);
        if(it == asum.end()) fsum[i] = fsum[i-1] + n;
        else fsum[i] = fsum[i-1] + (it - asum.begin());
    }

    while(q--)
    {
        int l,r;
        cin >> l >> r;

        cout << fsum[r] - fsum[l-1] << endl;
    }
}
