/*
Problem: Matrix Construction
Contest: AtCoder
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

struct Cell {
    int limit;
    int r, c;
};

void solve() 
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    vector<int> pos_a(n * m + 1, -1), pos_b(n * m + 1, -1);
    bool possible = true;

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if (pos_a[a[i]] != -1) possible = false;
        pos_a[a[i]] = i;
    }
    for(int i = 0; i < m; i++) {
        cin >> b[i];
        if (pos_b[b[i]] != -1) possible = false;
        pos_b[b[i]] = i;
    }

    if (!possible) {
        cout << "No" << endl;
        return;
    }
    int r_max_idx = 0;
    for (int i = 1; i < n; ++i) if (a[i] > a[r_max_idx]) r_max_idx = i;
    
    int c_max_idx = 0;
    for (int j = 1; j < m; ++j) if (b[j] > b[c_max_idx]) c_max_idx = j;

    vector<vector<int>> mat(n, vector<int>(m, 0));
    vector<bool> used(n * m + 1, false);
    for (int i = 0; i < n; ++i) {
        int val = a[i];
        if (pos_b[val] != -1) {
            int j = pos_b[val];
            mat[i][j] = val;
            used[val] = true;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (used[a[i]]) continue;
        
        if (a[i] > b[c_max_idx]) {
            cout << "No" << endl;
            return;
        }
        if (mat[i][c_max_idx] != 0) {
            cout << "No" << endl;
            return;
        }
        mat[i][c_max_idx] = a[i];
        used[a[i]] = true;
    }
    for (int j = 0; j < m; ++j) {
        if (used[b[j]]) continue;
        
        if (b[j] > a[r_max_idx]) {
            cout << "No" << endl;
            return;
        }
        if (mat[r_max_idx][j] != 0) {
            cout << "No" << endl;
            return;
        }
        mat[r_max_idx][j] = b[j];
        used[b[j]] = true;
    }
    vector<int> rem;
    for (int v = 1; v <= n * m; ++v) {
        if (!used[v]) rem.push_back(v);
    }
    vector<Cell> empty_cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mat[i][j] == 0) {
                empty_cells.push_back({min(a[i], b[j]), i, j});
            }
        }
    }

    if (rem.size() != empty_cells.size()) {
        cout << "No" << endl;
        return;
    }
    sort(empty_cells.begin(), empty_cells.end(), [](const Cell& x, const Cell& y) {
        return x.limit < y.limit;
    });
    for (size_t k = 0; k < empty_cells.size(); ++k) {
        if (rem[k] >= empty_cells[k].limit) {
            cout << "No" << endl;
            return;
        }
        mat[empty_cells[k].r][empty_cells[k].c] = rem[k];
    }
    cout << "Yes" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << mat[i][j] << (j == m - 1 ? "" : " ");
        }
        cout << endl;
    }
}

signed main() 
{
    SPEED;
    int t = 1;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}