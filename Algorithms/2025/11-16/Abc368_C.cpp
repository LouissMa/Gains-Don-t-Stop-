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
    vector<int> h(n);
    int t = 0;
    for(int i=0;i<n;i++)
    {
        cin>>h[i];
        t += h[i] / 5 * 3;
        h[i] %= 5;
        while(h[i] > 0)
        {
            t++;
            if(t % 3 == 0)
            {
                h[i] -= 3;
            }
            else h[i] --;
        }
    }
    cout<<t<<endl;
    return 0;
}