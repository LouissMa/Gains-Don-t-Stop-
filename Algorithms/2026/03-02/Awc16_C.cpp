#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct present {
    int p;
    int s;
    int num;
};

void solve(void) {
    int n, l, r, t;
    cin >> n >> l >> r >> t;
    vector<present> a;
    for (int i = 0; i < n; i++) {
        int p, s;
        cin >> p >> s;
        if (p < l || r < p) {
            continue;
        }
        if (s < t) {
            continue;
        }
        a.push_back({p, s, i + 1});
    }
    if (a.size() == 0) {
        cout << "-1\n";
        return;
    }
    sort(a.begin(),a.end(), [](const auto& l, const auto& r) {
        if (l.p != r.p) {
            return l.p < r.p;
        }
        if (l.s != r.s) {
            return r.s < l.s;
        }
        return l.num < r.num;
    });
    cout << a[0].num << '\n';
}

int main(void) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    solve();

    return 0;
}
