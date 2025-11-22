#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int MOD = 998244353;
const int MAXN = 2000005; // String length up to 10^6, combinations can reach 2*10^6

int fact[MAXN], invFact[MAXN];

int power(int base, int exp) {
    int res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int modInverse(int n) {
    return power(n, MOD - 2);
}

void precompute() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[MAXN - 1] = modInverse(fact[MAXN - 1]);
    for (int i = MAXN - 2; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

int nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

signed main()
{
    SPEED;
    precompute();
    string s;
    cin >> s;
    vector<int> cnt(10, 0);
    vector<vector<int>> Ks(10);
    for (char c : s) {
        int digit = c - '0';
        if (digit > 0) {
            Ks[digit - 1].push_back(cnt[digit - 1]);
        }
        cnt[digit]++;
    }
    int total_ans = 0;
    for (int d = 0; d < 9; d++) {
        int M = Ks[d].size();
        if (M == 0) continue;
        for (int j = 0; j < M; j++) {
            int k_val = Ks[d][j];
            int N_comb = k_val + M - 1 - j;
            int R_comb = M - j;
            total_ans = (total_ans + nCr(N_comb, R_comb)) % MOD;
        }
    }
    cout << total_ans << endl;
    
    return 0;
}