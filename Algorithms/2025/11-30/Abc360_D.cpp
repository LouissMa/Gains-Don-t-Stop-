#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,t;
    cin>>n>>t;
    vector<int> a,b;
    string s;
    cin>>s;
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        if(s[i] == '1') a.push_back(x);
        else b.push_back(x);
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int ans = 0;
    for(int i=0,l=0,r=0;i<a.size();i++)
    {
        while(r < b.size() && b[r] - a[i] <= 2 * t) r++;
        while(l < b.size() && b[l] < a[i]) l++;
        ans += r - l;
    }
    cout<<ans<<endl;
    return 0;
}