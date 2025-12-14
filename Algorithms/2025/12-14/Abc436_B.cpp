#include <bits/stdc++.h>
using namespace std;
int g[100][100];
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n,x,y,c,i,j;
	cin>>n;
	x=0;
	y=n/2;
	for(i=0;i<n;i++)
	{
		if(i>0)x=(x+1)%n;
		for(j=0;j<n;j++)
		{
			if(j>0)
			{
				x=(x+n-1)%n;
				y=(y+1)%n;
			}
			g[x][y]=i*n+j+1;
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)cout<<g[i][j]<<' ';
		cout<<'\n';
	}
	return 0;
}