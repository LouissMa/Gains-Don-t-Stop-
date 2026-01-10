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
    vector<int> b(n);
    int sum_b = 0;
    for(int i=0;i<n;i++)
    {
        cin>>b[i];
        sum_b += b[i];
    }
    int sum = sum_b / (n-1);
    for(int i=0;i<n;i++)
    {
        cout<<sum - b[i]<<" ";
    }
    cout<<"\n";
    return 0;
}