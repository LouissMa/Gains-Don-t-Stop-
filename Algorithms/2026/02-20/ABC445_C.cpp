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
    vector<int> a(n);
    for(int i=0;i<n;i++) 
    {
        cin>>a[i];
        a[i] --;
    }
    for(int i=n-1;i>=0;i--)
    {
        a[i] = a[a[i]];
    }
    for(int i=0;i<n;i++)
    {
        cout<<a[i] + 1<<" ";
    }
    cout<<endl;
    return 0;
}