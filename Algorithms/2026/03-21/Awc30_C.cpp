#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, k, ans;
int s[N];
int main()
{
    cin >> n >> k;
    for (int i=1; i<=n; i++)
        cin >> s[i];
    int cnt = 0;
    bool flag = 0;
    for (int i=1; i<=n; i++)
    {
        if (s[i]==1)
        {
            cnt++;
            if (cnt>=k && flag==0)
            {
                ans++;
                flag = 1;
            }
        }
        else 
        {
            cnt = 0;
            flag = 0;
        }
    }
    cout << ans << endl;
    return 0;
}