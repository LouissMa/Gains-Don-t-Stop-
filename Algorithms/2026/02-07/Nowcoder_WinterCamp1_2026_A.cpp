#include <iostream>
#include <vector>

using namespace std;

long long MOD = 998244353;

// 快速幂计算逆元
long long qpow(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long inv(long long n) {
    return qpow(n, MOD - 2);
}

// 定义数字0-9对应的灯管状态（1-7号灯管）
// 根据图2映射：1(顶), 2(左上), 3(右上), 4(中), 5(左下), 6(右下), 7(底)
int digit_masks[10][7] = {
    {1, 1, 1, 0, 1, 1, 1}, // 0
    {0, 0, 1, 0, 0, 1, 0}, // 1
    {1, 0, 1, 1, 1, 0, 1}, // 2
    {1, 0, 1, 1, 0, 1, 1}, // 3
    {0, 1, 1, 1, 0, 1, 0}, // 4
    {1, 1, 0, 1, 0, 1, 1}, // 5
    {1, 1, 0, 1, 1, 1, 1}, // 6
    {1, 0, 1, 0, 0, 1, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
};

void solve() {
    int C;
    cin >> C;
    vector<long long> p(7);
    long long inv100 = inv(100);
    for (int i = 0; i < 7; ++i) cin >> p[i];

    // 1. 计算单个数字产生的概率
    long long prob_digit[10];
    for (int d = 0; d <= 9; ++d) {
        long long cur = 1;
        for (int i = 0; i < 7; ++i) {
            long long p_on = p[i] * inv100 % MOD;
            long long p_off = (100 - p[i]) * inv100 % MOD;
            if (digit_masks[d][i]) {
                cur = cur * p_on % MOD;
            } else {
                cur = cur * p_off % MOD;
            }
        }
        prob_digit[d] = cur;
    }

    // 2. 预处理 0 到 C 每个 4 位数（含前导零）出现的概率
    auto get_val_prob = [&](int v) {
        long long res = 1;
        int temp = v;
        for (int i = 0; i < 4; ++i) {
            res = res * prob_digit[temp % 10] % MOD;
            temp /= 10;
        }
        return res;
    };

    vector<long long> prob_val(C + 1);
    for (int v = 0; v <= C; ++v) {
        prob_val[v] = get_val_prob(v);
    }

    // 3. 计算 A + B = C 的概率和
    long long ans = 0;
    for (int A = 0; A <= C; ++A) {
        int B = C - A;
        ans = (ans + prob_val[A] * prob_val[B]) % MOD;
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}