#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,A,B;
    cin>>n>>A>>B;
    string s;
    cin>>s;
    int ans = 0;
    vector<int> suma(n+1,0),sumb(n+1,0);
    for(int i=0;i<n;i++)
    {
        suma[i+1] = suma[i] + (s[i]=='a'?1:0);
        sumb[i+1] = sumb[i] + (s[i]=='b'?1:0);
    }
    int r1 = 0,r2 = -1;
    for(int l=0;l<n;l++)
    {
        r1 = max(r1,l);
        while(r1 < n && suma[r1+1] - suma[l] < A) r1++;
        if(r1 >= n) break;
        if(sumb[r1+1] - sumb[l] >= B) continue; 
        r2 = max(r2,r1);
        while(r2+1 < n && sumb[r2+2] - sumb[l] < B) r2++;
        ans += (r2-r1+1);
    }
    cout<<ans<<endl;
    return 0;
}