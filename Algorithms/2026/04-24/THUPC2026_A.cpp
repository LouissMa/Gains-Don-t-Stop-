#include <iostream>
#include <vector>

using namespace std;

signed main (void) {
	int t;
	cin>>t;
	while (t--) {
		int n, k;
		cin>>n>>k;
		vector<int> a(k), b(n);
		for (int& v: a) cin>>v;
		for (int& v: b) cin>>v;
		int m = 0;
		for (int v: b) m+=k+1-v;
		if (m>1000) {
			cout<<-1<<endl;
			continue;
		}
		cout<<m<<endl;
		for (int i=k; i>=1; --i) for (int j=0; j<n; ++j) if (b[j]==i) {
			for (int i=1; i<=k+1-b[j]; ++i) cout<<j+1<<" ";
		}
		cout<<endl;
	}
	return 0;
}
