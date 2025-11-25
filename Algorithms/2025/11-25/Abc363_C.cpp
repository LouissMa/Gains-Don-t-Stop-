#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,k;
    cin>>n>>k;
    string s;
    cin>>s;
    int ans = 0;
    sort(s.begin(),s.end());
    do{
        bool ok = true;
        for(int i=0;i<=n-k;i++)
        {
            bool flag = true;
            for(int j=0;j<k-1-j;j++)
            {
                if(s[i+j] != s[i+k-1-j])
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                ok = false;
                break;
            }
        }
        if(ok) ans++;
    }while(next_permutation(s.begin(),s.end()));
    cout<<ans<<endl;
    return 0;
}