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
    for(int i=0;i<n;i++)
    {
        if(s[i] == 'O')
        {
            int j = i;
            while(j < n && s[j] == 'O' && j-i < k) j++;
            if(j-i == k) ans ++;
            i = j-1;
        }
        else continue;
    }
    cout<<ans<<endl;
    return 0;
}