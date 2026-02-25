#include <bits/stdc++.h>
using namespace std;
map<int,int>dp;
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n,i,a,ans=0;
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>a;
		dp[a]=max(dp[a],dp[a-1]+1);
		ans=max(ans,dp[a]);
	}
	cout<<ans<<'\n';
	return 0;
}