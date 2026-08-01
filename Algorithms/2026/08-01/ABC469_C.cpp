#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

signed main() {
    SPEED;

    int N;
    if (!(cin >> N)) return 0;
    string S;
    cin >> S;

    // cnt_x[i] stores the number of 'x' in the first i characters
    vector<int> cnt_x(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        cnt_x[i] = cnt_x[i - 1] + (S[i - 1] == 'x');
    }

    int R = 0;
    
    for (int k = 1; k <= N; ++k) {
        // We can safely evaluate the next bag R+1 if the number of 'x' bags 
        // encountered up to R is strictly less than our starting capacity k.
        while (R < N && cnt_x[R] <= k - 1) {
            R++;
        }
        
        // Takahashi can always eat at least the initial k sweets
        cout << max(k, R) << "\n";
    }

    return 0;
}