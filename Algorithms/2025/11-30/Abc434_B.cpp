#include <bits/stdc++.h>
using namespace std;
int s[100],c[100];
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	cout<<setiosflags(ios::fixed)<<setprecision(11);
	int n,m,i,a,b;
	cin>>n>>m;
	for(i=0;i<n;i++)
	{
		cin>>a>>b;
		a--;
		s[a]+=b;
		c[a]++;
	}
	for(i=0;i<m;i++)cout<<(double)s[i]/(double)c[i]<<'\n';
	return 0;
}