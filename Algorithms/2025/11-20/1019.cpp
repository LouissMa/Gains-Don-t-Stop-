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
    priority_queue<int,vector<int>,greater<int>> heap;
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        heap.push(x);
    }
    int res = 0;
    while(heap.size() > 1)
    {
        int a = heap.top();heap.pop();
        int b = heap.top();heap.pop();
        res += a + b;
        heap.push(a + b);
    }
    cout<<res<<endl;
    return 0;
}