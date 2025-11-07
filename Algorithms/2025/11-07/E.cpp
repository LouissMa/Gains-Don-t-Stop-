#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,x;
    cin>>n>>x;
    vector<int> A(n),P(n),B(n),Q(n);
    for(int i=0;i<n;i++)
    {
        cin>>A[i]>>P[i]>>B[i]>>Q[i];
        if(A[i] * Q[i] < B[i] * P[i])
        {
            swap(A[i],B[i]);
            swap(P[i],Q[i]);
        }
    }
    auto check = [&](int u)
    {
        int ans = 0;
        for(int i=0;i<n;i++)
        {
            int res = 1e18;
            for(int j=0;j<=100;j++)
            {
                int v = 1LL * j * Q[i];
                int need = u - j * B[i];
                if(need > 0)
                {
                    v += 1LL * (need + A[i]-1) / A[i] * P[i];
                }
                res = min(res,v);
            }
            ans += res;
            if(ans > x) return false;
        }
        return ans <= x;
    };
    int l = 0,r = 1e9;
    while(l < r)
    {
        int mid = (l+r+1) >> 1;
        if(check(mid)) l = mid;
        else r = mid-1;
    }
    cout<<l<<endl;
    return 0;
}