#include <bits/stdc++.h>
using namespace std;
long long dp[200001][3];
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T;
	long long n,i,a;
	for(cin>>T;T>0;T--)
	{
		cin>>n;
		dp[0][0]=0;
		dp[0][1]=0;
		dp[0][2]=0;
		for(i=0;i<n;i++)
		{
			cin>>a;
			dp[i+1][0]=dp[i][0]+a;
			dp[i+1][1]=dp[i][1];
			dp[i+1][2]=dp[i][2]+a;
			dp[i+1][1]=max(dp[i+1][1],dp[i+1][0]-(i+1)*(i+2));
			dp[i+1][2]=max(dp[i+1][2],dp[i+1][1]+(i+1)*(i+2));
		}
		cout<<max(dp[n][0],dp[n][2])<<'\n';
	}
	return 0;
}