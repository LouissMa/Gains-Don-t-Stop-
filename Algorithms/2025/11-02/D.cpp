#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;


const int INF = 2e18; // 2 * 10^18

signed main()
{
    SPEED;
    int n;
    cin >> n;
    int total_sum = 0;
    set<int> positions;
    map<int, int> d_values;

    positions.insert(0);
    d_values[0] = INF;


    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
    
        auto it = positions.insert(x).first;

        int pos_L = -1, dist_L = INF;
        int pos_R = -1, dist_R = INF;

        if (it != positions.begin()) {
            pos_L = *std::prev(it);
            dist_L = x - pos_L;
        }
        if (std::next(it) != positions.end()) {
            pos_R = *std::next(it);
            dist_R = pos_R - x;
        }

        int d_new = min(dist_L, dist_R);
        total_sum += d_new;
        d_values[x] = d_new;
        if (pos_L != -1) {
            int d_L_old = d_values[pos_L];
            int d_L_new = min(d_L_old, dist_L);
            if (i == 1) {
                total_sum += d_L_new; 
            } else {
                total_sum = total_sum - d_L_old + d_L_new;
            }
            d_values[pos_L] = d_L_new;
        }

        if (pos_R != -1) {
            int d_R_old = d_values[pos_R];
            int d_R_new = min(d_R_old, dist_R);
            total_sum = total_sum - d_R_old + d_R_new;
            d_values[pos_R] = d_R_new;
        }
        cout << total_sum << "\n";
    }

    return 0;
}