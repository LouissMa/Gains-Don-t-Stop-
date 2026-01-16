#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T;
	long long s,k,m;
	for(cin>>T;T>0;T--)
	{
		cin>>s>>k>>m;
		m%=k*2;
		if(m<k)cout<<max(0LL,s-m)<<'\n';
		else cout<<max(0LL,min(s,k)-m+k)<<'\n';
	}
	return 0;
}