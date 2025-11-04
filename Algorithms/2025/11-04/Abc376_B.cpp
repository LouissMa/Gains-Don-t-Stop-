#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,q;
    cin>>n>>q;
    array<int,2> a{0,1};
    int ans = 0;
    auto work = [&](int i,int x)
    {
        if(abs(a[!i] - a[i]) + abs(a[!i] - x) == abs(a[i] - x))
        {
            ans += n - abs(a[i] - x);
        }
        else{
            ans += abs(a[i] - x);
        }
        a[i] = x;
    };
    for(int i=0;i<q;i++)
    {
        char c;
        int x;
        cin>>c>>x;
        x--;
        work(c == 'L'?0:1,x);
    }
    cout<<ans<<endl;
    return 0;
}