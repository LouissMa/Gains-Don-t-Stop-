#include <bits/stdc++.h>
using namespace std;
int n,t;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		if(n<=3)cout<<-1<<'\n';
		else{
			if(n&1)cout<<1<<'\n';
			else cout<<2<<'\n';
		}
	}
}