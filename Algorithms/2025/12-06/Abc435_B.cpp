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
    vector<int> pre(n+1);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        pre[i+1] = pre[i] + a[i];
    }
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
            int sum = pre[j+1] - pre[i];
            bool ok = true;
            for(int k=i;k<=j;k++)
            {
                if(sum % a[k] == 0) 
                {
                    ok = false;
                    break;
                }
            }
            if(ok) ans ++;
        }
    }
    cout<<ans<<endl;
    return 0;
}