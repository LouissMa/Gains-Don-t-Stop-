#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

int power(int a, i64 b, int p) {
    int res = 1;
    for (; b; b /= 2, a = 1LL * a * a % p) {
        if (b & 1) {
            res = 1LL * res * a % p;
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    i64 K;
    std::cin >> N >> K;
    
    std::vector<int> P(N);
    for (int i = 0; i < N; i++) {
        std::cin >> P[i];
        P[i]--;
    }
    
    std::vector<bool> vis(N);
    for (int i = 0; i < N; i++) {
        if (vis[i]) {
            continue;
        }
        
        int j = i;
        std::vector<int> a;
        while (!vis[j]) {
            vis[j] = true;
            a.push_back(j);
            j = P[j];
        }
        
        i64 d = power(2, K, a.size());
        for (int x = 0; x < a.size(); x++) {
            P[a[x]] = a[(x + d) % a.size()];
        }
    }
    for (int i = 0; i < N; i++) {
        std::cout << P[i] + 1 << " \n"[i == N - 1];
    }
    
    return 0;
}