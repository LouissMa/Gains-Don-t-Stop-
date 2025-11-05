#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, M;
    std::cin >> N >> M;
    
    std::vector<std::vector<std::array<int, 2>>> adj(N);
    std::vector<int> A(M), B(M), C(M);
    for (int i = 0; i < M; i++) {
        std::cin >> A[i] >> B[i] >> C[i];
        A[i]--;
        B[i]--;
        adj[A[i]].push_back({B[i], C[i]});
        adj[B[i]].push_back({A[i], C[i]});
    }
    
    auto sp = [&](int s) {
        std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<>> q;
        q.emplace(0LL, s);
        std::vector dis(N, inf);
        
        while (!q.empty()) {
            auto [d, x] = q.top();
            q.pop();
            
            if (dis[x] != inf) {
                continue;
            }
            dis[x] = d;
            
            for (auto [y, w] : adj[x]) {
                q.emplace(d + w, y);
            }
        }
        
        return dis;
    };
    
    auto d1 = sp(0);
    auto dn = sp(N - 1);
    
    std::vector<int> u;
    for (int i = 0; i < N; i++) {
        if (d1[i] + dn[i] == dn[0]) {
            u.push_back(i);
        }
    }
    std::sort(u.begin(), u.end(),
        [&](int i, int j) {
            return d1[i] < d1[j];
        });
    
    std::vector<int> pos(N, -1);
    int m = u.size();
    for (int i = 0; i < m; i++) {
        pos[u[i]] = i;
    }
    
    std::vector<int> f(m);
    for (int x = 0; x < N; x++) {
        for (auto [y, w] : adj[x]) {
            if (d1[x] + w + dn[y] == dn[0]) {
                f[pos[x]]++;
                f[pos[y]]--;
            }
        }
    }
    
    for (int i = 1; i < m; i++) {
        f[i] += f[i - 1];
    }
    
    for (int i = 0; i < M; i++) {
        bool ans = false;
        if (pos[A[i]] != -1 && pos[B[i]] != -1 && std::abs(pos[A[i]] - pos[B[i]]) == 1 && f[std::min(pos[A[i]], pos[B[i]])] == 1) {
            ans = true;
        }
        std::cout << (ans ? "Yes" : "No") << "\n";
    }
    
    return 0;
}