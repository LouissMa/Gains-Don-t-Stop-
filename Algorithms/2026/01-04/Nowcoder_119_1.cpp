#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

set<int> s;

void double_it()
{
    for(int i=1;i<=1000;i++)
    {
        s.insert(i*i);
    }
}
signed main()
{
    SPEED;
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a.begin(),a.end(),greater<int>());
    double_it();
    for(int i=0;i<n;i++)
    {
        if(!s.count(a[i]))
        {
            cout<<a[i]<<endl;
            return 0;
        }
    }
}