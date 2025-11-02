#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
using namespace std; 
const int MAXN = 500000+10;
priority_queue<int,vector<int>,greater<int> >s; // 小根堆 
priority_queue<int,vector<int>,less<int> >b;// 大根堆
 
int a[MAXN],u[MAXN];
int main()
{
	int m,n;
	cin>>m>>n;
	for(int i=1;i<=m;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&u[i]);
	int p=0;
	for(int i=1;i<=n;i++)
	{
		while(p<u[i])
		{
			p++;
			b.push(a[p]);
			s.push(b.top());
			b.pop();
		}
		printf("%d\n",s.top());
		b.push(s.top());
		s.pop();
	}
	return 0;
} 
