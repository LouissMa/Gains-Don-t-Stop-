#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    string s;
    cin>>s;
    int a,b;
    cin>>a>>b;
    int n = s.size();
    for(int i=a;i<= (n - b - 1);i++) cout<<s[i];
    cout<<"\n";
    return 0;
}