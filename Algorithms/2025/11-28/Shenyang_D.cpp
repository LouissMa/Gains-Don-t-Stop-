#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin>>n;
    vector<array<int,3>> a(n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<3;j++) cin>>a[i][j];
    }
    vector<int> p(3);
    iota(p.begin(),p.end(),0);
    int ans = 1000;
    do{
        set<int> s;
        for(int i=0;i<n;i++) s.insert(i);
        int res = 1;
        for(auto c : p)
        {
            for(auto it = s.begin(); it != s.end();)
            {
                if(a[*it][c]) it = s.erase(it);
                else it = next(it);
            }
            if(!s.empty()) res++;
        }
        ans = min(ans,res);
    }while(next_permutation(p.begin(),p.end()));
    cout<<ans<<endl;
    return 0;
}