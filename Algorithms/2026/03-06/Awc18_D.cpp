#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    vector<bool> dp(k + 1, false);
    dp[0] = true;
    for (int i = 0; i < n; i++) {
        vector<bool> dp2(k + 1, false);
        for (int j = 0; j <= k; j++) {
            if (dp[j]) {
                dp2[j] = true;
                if (j + c[i] <= k) dp2[j + c[i]] = true;
            }
        }
        dp = dp2;
    }
    int ans = 0;
    for (int i = 0; i <= k; i++) {
        if (dp[i]) ans = i;
    }
    cout << ans << endl;

    return 0;
}