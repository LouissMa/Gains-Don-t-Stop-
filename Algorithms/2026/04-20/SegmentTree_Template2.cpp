#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 1e5 + 10;
int a[N], mod;

struct tree {
    int l, r;
    int pre;   // 区间和
    int add;   // 加法懒标记
    int mul;   // 乘法懒标记
} t[N * 4];

void push_up(int p) {
    t[p].pre = (t[p * 2].pre + t[p * 2 + 1].pre) % mod;
}

void build(int p, int l, int r) {
    t[p].l = l;
    t[p].r = r;
    t[p].add = 0;
    t[p].mul = 1;
    if (l == r) {
        t[p].pre = a[l] % mod;
        return;
    }
    int mid = (l + r) >> 1;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    push_up(p);
}

void push_down(int p) {
    if (t[p].mul != 1 || t[p].add != 0) {
        int ls = p * 2, rs = p * 2 + 1;

        // 左儿子
        t[ls].pre = (t[ls].pre * t[p].mul % mod + t[p].add * (t[ls].r - t[ls].l + 1) % mod) % mod;
        t[ls].mul = t[ls].mul * t[p].mul % mod;
        t[ls].add = (t[ls].add * t[p].mul % mod + t[p].add) % mod;

        // 右儿子
        t[rs].pre = (t[rs].pre * t[p].mul % mod + t[p].add * (t[rs].r - t[rs].l + 1) % mod) % mod;
        t[rs].mul = t[rs].mul * t[p].mul % mod;
        t[rs].add = (t[rs].add * t[p].mul % mod + t[p].add) % mod;

        t[p].mul = 1;
        t[p].add = 0;
    }
}

void change_mul(int p, int x, int y, int k) {
    if (x <= t[p].l && t[p].r <= y) {
        t[p].pre = t[p].pre * k % mod;
        t[p].mul = t[p].mul * k % mod;
        t[p].add = t[p].add * k % mod;
        return;
    }
    push_down(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (x <= mid) change_mul(p * 2, x, y, k);
    if (y > mid) change_mul(p * 2 + 1, x, y, k);
    push_up(p);
}

void change_add(int p, int x, int y, int k) {
    if (x <= t[p].l && t[p].r <= y) {
        t[p].pre = (t[p].pre + k * (t[p].r - t[p].l + 1) % mod) % mod;
        t[p].add = (t[p].add + k) % mod;
        return;
    }
    push_down(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (x <= mid) change_add(p * 2, x, y, k);
    if (y > mid) change_add(p * 2 + 1, x, y, k);
    push_up(p);
}

int ask(int p, int x, int y) {
    if (x <= t[p].l && t[p].r <= y) return t[p].pre % mod;
    push_down(p);
    int mid = (t[p].l + t[p].r) >> 1;
    int ans = 0;
    if (x <= mid) ans = (ans + ask(p * 2, x, y)) % mod;
    if (y > mid) ans = (ans + ask(p * 2 + 1, x, y)) % mod;
    return ans % mod;
}

signed main() {
    SPEED;
    int n, q;
    cin >> n >> q >> mod;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);

    for (int i = 1; i <= q; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            int k;
            cin >> k;
            change_mul(1, x, y, k % mod);
        } else if (op == 2) {
            int k;
            cin >> k;
            change_add(1, x, y, k % mod);
        } else {
            cout << ask(1, x, y) % mod << '\n';
        }
    }
    return 0;
}