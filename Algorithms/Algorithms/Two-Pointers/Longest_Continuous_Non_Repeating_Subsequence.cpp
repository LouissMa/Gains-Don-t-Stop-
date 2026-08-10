#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5 + 10;
int a[N];
int s[N];
signed main()
{
    SPEED;
    int n;
    cin >> n;
    for(int i = 0; i < n ; i ++) cin >> a[i];
    int res = 0;
    int j = 0;
    for(int i = 0; i < n; i ++)
    {
        s[a[i]] ++;
        while(s[a[i]] > 1)
        {
            s[a[j]] --;
            j ++;
        }
        res = max(res, i - j + 1);
    }
    cout<< res << "\n";
    return 0;
}