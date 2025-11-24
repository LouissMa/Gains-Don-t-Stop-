#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

struct DSU
{
    vector<int> f, siz;
    DSU(){}
    DSU(int n)
    {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    int find(int x)
    {
        while(x != f[x]) x = f[x] = find(f[x]);
        return x;
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
    bool merge(int x,int y)
    {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
};
signed main()
{
    SPEED;
    int n,q;
    cin>>n>>q;
    DSU dsu(n);
    vector<int> L(q),R(q),C(q);
    for(int i=0;i<q;i++) 
    {
        cin>>L[i]>>R[i]>>C[i];
        L[i] --;
    }
    vector<int> p(q);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int i, int j) { return C[i] < C[j]; });
    int ans = 0;
    for(int i : p)
    {
        ans += C[i];
        for (int x = dsu.find(L[i]); x < R[i] - 1; x = dsu.find(x)) {
            dsu.merge(x + 1, x);
            ans += C[i];
        }
    }
    if (dsu.find(0) != n - 1) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }
    return 0;
}