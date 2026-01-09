#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define fi first
#define se second
#define db double
using namespace std;

const int N = (int)5e5 + 5;

int T, n, nb, nc, nz, a[N], cnt[N], pos[N][2], b[N], c[N], z[N], p[N];

void work(int cid) {
	cin >> n;
	nb = nc = nz = 0;
	for (int i = 1; i <= n; i++) {
		cnt[i] = 0;
		p[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		pos[a[i]][cnt[a[i]]++] = i;
	}
	for (int i = 1; i <= n; i++) {
		if (cnt[i] == 2) {
			b[++nb] = i;
		}
		if (cnt[i] == 0) {
			c[++nc] = i;
		}
	}
	for (int i = 1; i <= nb; i++) {
		int x = b[i];
		if (pos[x][0] != 1) {
			p[pos[x][0] - 1] = c[i];
			p[pos[x][1] - 1] = c[i];
		} else {
			z[++nz] = c[i];
			z[++nz] = c[i];
		}
	}
	int ans = cnt[a[1]] == 2;
	for (int i = 1; i <= n; i++) {
		if (cnt[a[i]] == 1) {
			z[++nz] = a[i];
		}
		if (!p[i]) {
			p[i] = z[nz--];
		}
	}
	cout << ans << '\n';
	for (int i = 1; i <= n; i++) {
		cout << p[i] << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int cid = 1; cid <= T; cid++) {
		work(cid);
	}

	return 0;
}