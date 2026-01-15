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
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int i = 0, j = 0, cnt = 0;
    while (i < n && j < n) {
        if (a[i] > b[j]) {
            cnt++;
            i++;
            j++;
        } else {
            i++;
        }
    }
    cout << n - cnt;
    return 0;
}