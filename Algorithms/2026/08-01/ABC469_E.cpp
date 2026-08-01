#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

signed main()
{
    SPEED;
    int N, K;
    if (!(cin >> N >> K)) return 0;
    string S;
    cin >> S;
    vector<int> pref_o(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        pref_o[i] = pref_o[i - 1] + (S[i - 1] == 'o' ? 1 : 0);
    }
    vector<double> pref_a(N + 1, 0.0);
    auto check = [&](double x) {
        // 构建权重前缀和
        for (int i = 1; i <= N; ++i) {
            double val = (S[i - 1] == 'o' ? 1.0 - x : -x);
            pref_a[i] = pref_a[i - 1] + val;
        }

        int max_j = 0;      
        double min_a = 0.0;  

        for (int r = 1; r <= N; ++r) {
            while (max_j + 1 <= r && pref_o[r] - pref_o[max_j + 1] >= K) {
                max_j++;
                min_a = min(min_a, pref_a[max_j]);
            }
        
            if (pref_o[r] >= K) {
                if (pref_a[r] - min_a >= 0) {
                    return true;
                }
            }
        }
        return false;
    };
    double L = 0.0, R = 1.0;
    for (int iter = 0; iter < 80; ++iter) {
        double mid = L + (R - L) / 2.0;
        if (check(mid)) {
            L = mid; // 如果可行，尝试寻找更高的胜率
        } else {
            R = mid; // 如果不可行，降低胜率要求
        }
    }

    cout << fixed << setprecision(10) << L << "\n";

    return 0;
}