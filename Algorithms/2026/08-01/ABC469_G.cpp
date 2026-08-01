#include <bits/stdc++.h>
using namespace std;

long long MOD;

struct Matrix {
    int n;
    vector<vector<long long>> mat;
    Matrix(int n) : n(n), mat(n, vector<long long>(n, 0)) {}
    
    static Matrix identity(int n) {
        Matrix res(n);
        for (int i = 0; i < n; i++) res.mat[i][i] = 1;
        return res;
    }
    
    Matrix operator*(const Matrix& other) const {
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (mat[i][k] == 0) continue;
                for (int j = 0; j < n; j++) {
                    res.mat[i][j] += mat[i][k] * other.mat[k][j];
                }
            }
            for (int j = 0; j < n; j++) {
                res.mat[i][j] %= MOD;
            }
        }
        return res;
    }
};

// 专门针对 T_n 矩阵的 O(K^2) 快速左乘优化
Matrix fast_mult(const Matrix& Tn, const Matrix& M) {
    int K = M.n;
    Matrix res(K);
    for (int j = 0; j < K; j++) {
        long long sum = 0;
        for (int k = 0; k < K; k++) {
            sum += Tn.mat[0][k] * M.mat[k][j];
        }
        res.mat[0][j] = sum % MOD;
    }
    for (int i = 1; i < K; i++) {
        for (int j = 0; j < K; j++) {
            res.mat[i][j] = M.mat[i - 1][j];
        }
    }
    return res;
}

Matrix power(Matrix a, long long b) {
    Matrix res = Matrix::identity(a.n);
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int K;
    if (!(cin >> K)) return 0;

    vector<string> S(K + 1);
    for (int i = 1; i <= K; i++) {
        cin >> S[i];
    }

    long long N;
    cin >> N;
    string T_str;
    cin >> T_str;

    MOD = T_str.length();

    vector<int> B(2 * K + 3, 0);
    vector<long long> A_val(K + 1, 0);

    // 计算前 K 个基础字符串的独立效果
    for (int i = 1; i <= K; i++) {
        long long shift = 0;
        int rev = 0;
        for (char c : S[i]) {
            if (c == 'a') {
                shift = (shift + (rev ? -1 : 1)) % MOD;
            } else {
                rev = 1 - rev;
            }
        }
        B[i] = rev;
        A_val[i] = (shift % MOD + MOD) % MOD;
    }

    long long final_B = 0, final_A = 0;

    if (N <= K) {
        final_B = B[N];
        final_A = A_val[N];
    } else {
        // 利用线性递推生成足够的 B 序列 (B 具有 K+1 的完美周期)
        for (int i = K + 1; i <= 2 * K + 2; i++) {
            int sum = 0;
            for (int j = 1; j <= K; j++) {
                sum = (sum + B[i - j]) % 2;
            }
            B[i] = sum;
        }

        // 构建单个周期块矩阵 M_block
        Matrix M_block = Matrix::identity(K);
        for (int i = 1; i <= K + 1; i++) {
            int n = K + i;
            Matrix Tn(K);
            Tn.mat[0][0] = 1;
            for (int j = 2; j <= K; j++) {
                int p_sum = 0;
                for (int m = 1; m <= j - 1; m++) {
                    p_sum = (p_sum + B[n - m]) % 2;
                }
                long long val = (p_sum == 1) ? -1 : 1;
                Tn.mat[0][j - 1] = (val + MOD) % MOD;
            }
            for (int r = 1; r < K; r++) {
                Tn.mat[r][r - 1] = 1;
            }
            M_block = fast_mult(Tn, M_block);
        }

        long long blocks = (N - K) / (K + 1);
        long long rem = (N - K) % (K + 1);

        // 构建剩余的零头矩阵 M_rem
        Matrix M_rem = Matrix::identity(K);
        for (int i = 1; i <= rem; i++) {
            int n = K + i;
            Matrix Tn(K);
            Tn.mat[0][0] = 1;
            for (int j = 2; j <= K; j++) {
                int p_sum = 0;
                for (int m = 1; m <= j - 1; m++) {
                    p_sum = (p_sum + B[n - m]) % 2;
                }
                long long val = (p_sum == 1) ? -1 : 1;
                Tn.mat[0][j - 1] = (val + MOD) % MOD;
            }
            for (int r = 1; r < K; r++) {
                Tn.mat[r][r - 1] = 1;
            }
            M_rem = fast_mult(Tn, M_rem);
        }

        // 合并所有矩阵
        Matrix M_pow = power(M_block, blocks);
        Matrix M_final = M_rem * M_pow;

        vector<long long> A_vec(K);
        for (int i = 0; i < K; i++) {
            A_vec[i] = A_val[K - i];
        }

        vector<long long> A_res(K, 0);
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < K; j++) {
                A_res[i] = (A_res[i] + M_final.mat[i][j] * A_vec[j]) % MOD;
            }
        }

        final_A = A_res[0];
        final_B = B[(N - 1) % (K + 1) + 1];
    }

    // 将最终效果 (B_N, A_N) 实施到原字符串 T 上
    string res = "";
    for (int i = 0; i < MOD; i++) {
        res += T_str[(i + final_A) % MOD];
    }
    if (final_B == 1) {
        reverse(res.begin(), res.end());
    }

    cout << res << "\n";
    return 0;
}