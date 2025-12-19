#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n,k;
    cin>>n>>k;
    priority_queue<int,vector<int>,greater<int>> q;
    for(int i=0;i<n;i++) 
    {
        int x;
        cin>>x;
        q.push(x);
    }
    int sum = 0;
    int ans = 0;
    while(sum <= k)
    {
        int x = q.top();
        sum += x;
        ans ++;
        q.pop();
        q.push(2 * x);
    }
    cout<<ans-1<<endl;
    return 0;
}