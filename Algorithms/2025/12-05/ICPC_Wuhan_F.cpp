#include <bits/stdc++.h>
using namespace std;

#define int long long
const int maxn = 1e6 + 5;

int f[maxn];
vector<int> vec[maxn];
signed main()
{
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin >> T;
	while (T--)
	{
		int n, q; cin >> n >> q;
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 1; i <= q; i++)
		{
			int l, r; cin >> l >> r;
			vec[l].emplace_back(r);
		}
		for (int i = 1; i <= n; i++) f[i] = -0x3f3f3f3f; f[0] = 0;
		for (int i = 0; i < n; i++)
		{
			f[i + 1] = max(f[i + 1], f[i]);
			for (int r : vec[i + 1]) f[r] = max(f[r], f[i] + 1);
		}

		int res = f[n];
		cout << (32 - __builtin_clz(res)) << "\n";
	}
	return 0;
}