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
    int maxx = 0;
    int sum = 0;
    vector<int> a(n);
    vector<string> s(n);
    for(int i=0;i<n;i++)
    {
        cin>>s[i]>>a[i];
        if(s[i] == "pig")
        {
            maxx = max(maxx,a[i]);
        }
    }
    for(int i=0;i<n;i++)
    {
        if(a[i] < maxx && s[i] != "pig") sum += a[i];
    }
    cout<<sum + maxx<<"\n";
}