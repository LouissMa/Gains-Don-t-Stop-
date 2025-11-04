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
    vector<int> a(n),b(n-1);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n-1;i++) cin>>b[i];
    sort(a.begin(),a.end(),greater<int>());
    sort(b.begin(),b.end(),greater<int>());
    int i=0;
    while(i < n-1 && b[i] >= a[i]) i++;
    for(int j=i;j<n-1;j++)
    {
        if(b[j] < a[j+1])
        {
            cout<<-1<<"\n";
            return 0;
        }
    }
    cout<<a[i]<<"\n";
    return 0;
}