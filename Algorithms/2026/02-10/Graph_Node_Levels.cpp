#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 1e5 + 10;
int h[N], e[N * 2], ne[N * 2], idx;
int d[N];
int n, m;

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int bfs() {
    queue<int> q;
    memset(d, -1, sizeof d);
    q.push(1);
    d[1] = 0; // 初始距离设为0更合理
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (d[j] != -1) continue;
            d[j] = d[t] + 1; // 修正此处
            q.push(j);
        }
    }
    return d[n];
}

signed main() {
    SPEED;
    cin >> n >> m;
    memset(h, -1, sizeof h);
    idx = 0;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }
    cout << bfs() << endl;
    return 0;
}