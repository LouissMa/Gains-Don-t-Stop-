#include <bits/stdc++.h>
using namespace std;
vector<int>ansv[2];
queue<int>q;
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T,n,i,a,cmin,cur;
	for(cin>>T;T>0;T--)
	{
		cin>>n>>cmin;
		for(i=1;i<n;i++)
		{
			cin>>a;
			if(a<cmin)
			{
				q.push(cmin);
				cmin=a;
			}
			else
			{
				while(!q.empty()&&q.front()<a)
				{
					ansv[0].push_back(q.front());
					ansv[1].push_back(a);
					q.pop();
				}
				ansv[0].push_back(cmin);
				ansv[1].push_back(a);
			}
		}
		if(!q.empty())cout<<"No\n";
		else
		{
			cout<<"Yes\n";
			for(i=0;i<n-1;i++)cout<<ansv[0][i]<<' '<<ansv[1][i]<<'\n';
		}
		for(i=0;i<2;i++)ansv[i].clear();
		while(!q.empty())q.pop();
	}
	return 0;
}