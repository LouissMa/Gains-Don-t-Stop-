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
    string s;
    cin>>s;
    int t = s.size();
    int d = n - t;
    for(int i=0;i<d;i++) cout<<"o";
    cout<<s<<endl;
    return 0;
}