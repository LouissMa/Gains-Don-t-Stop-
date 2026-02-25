#include <bits/stdc++.h>
using namespace std;
int vis[101];
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n,m,l,i,j,a,ans;
	cin>>n>>m;
	for(i=0;i<n;i++)
	{
		cin>>l;
		ans=0;
		for(j=0;j<l;j++)
		{
			cin>>a;
			if(vis[a]==0&&ans==0)
			{
				vis[a]=1;
				ans=a;
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}