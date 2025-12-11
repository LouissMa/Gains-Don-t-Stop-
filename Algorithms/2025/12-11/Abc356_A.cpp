#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,l,r;
    cin>>n>>l>>r;
    vector<int> a(n);
    iota(a.begin(),a.end(),1);
    l--;
    reverse(a.begin()+l,a.begin()+r);
    for(int i=0;i<n;i++) cout<<a[i]<<" \n"[i==n-1];
    return 0;
}