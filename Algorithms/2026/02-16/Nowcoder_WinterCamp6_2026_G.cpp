#include<bits/stdc++.h>
using namespace std;

#define int long long
#define mod 998244353
#define MAXN 200005

int n,m,l,X[MAXN],Y[MAXN];

inline void solve(){
	scanf("%lld%lld%lld",&n,&m,&l);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&X[i]),X[i] += X[i - 1];
	for( int i = 1 ; i <= m ; i ++ ) scanf("%lld",&Y[i]);
	//对于每一条缝隙分析
	int now = l,pnt = 1;
	for( int i = 1 ; i <= n ; i ++ ){
		while( pnt <= m && now <= X[i] ) now += Y[pnt],pnt ++;
		if( now > X[i] && now - l < X[i] ){ puts("YES"); return; }
	}
	puts("NO");
}

signed main(){
	solve();
	return 0;
}