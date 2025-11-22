#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
int get_len(int x) 
{
    return to_string(x).length();
}

signed main()
{
    SPEED;
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<map<int, int>> cnt(11); 
    for(int i = 0; i < n; i++) 
    {
        cin >> a[i];
        int len = get_len(a[i]);
        int rem = a[i] % m;
        cnt[len][rem]++;
    }

    int ans = 0;
    for(int i = 0; i < n; i++) {
        int current_val = a[i] % m;
        int p10 = 10;
        for(int k = 1; k <= 10; k++) {
            int val = (current_val * (p10 % m)) % m;
            int need_rem = (m - val) % m;
            if(cnt[k].count(need_rem)) {
                ans += cnt[k][need_rem];
            }
            p10 = (p10 * 10) % m;
        }
    }

    cout << ans << endl;
    return 0;
}