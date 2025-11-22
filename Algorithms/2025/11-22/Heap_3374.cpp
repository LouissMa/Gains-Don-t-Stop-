#include<bits/stdc++.h>
using namespace std;
const int Maxn=500005;
int n,s[Maxn],m;
int lowbit(int x)
{
	return x&(-x);
}
struct node
{
	int c[Maxn];
	void add(int x,int d)//修改
	{
		s[x]+=d;
		for(int i=x;i<=n;i+=lowbit(i))
			c[i]+=d;
	}
	int sum(int x)//查询
	{
		int ans=0;
		for(int i=x;i>0;i-=lowbit(i))
			ans+=c[i];
		return ans;
	}
	void init()//初始化
	{
		memset(c,0,sizeof(c));
		for(int i=1;i<=n;i++)
			for(int j=i-lowbit(i)+1;j<=i;j++)
				c[i]=c[i]+s[j];
	}
	void print()//用来调试的输出
	{
		for(int i=1;i<=n;i++)
			printf("%d ",s[i]);
		cout <<"     ";
		for(int i=1;i<=n;i++)
			printf("%d ",c[i]);
		cout << endl;
	}
}a;
int main()
{
	cin >> n >> m;
	for(int i=1;i<=n;i++)//输入
		scanf("%d",&s[i]);
	a.init();//初始化
	for(int i=1;i<=m;i++)
	{
		//a.print();//调试
		int b,x,y;
		scanf("%d%d%d",&b,&x,&y);
		if(b==1)//操作1
			a.add(x,y);//把x为加上y
		else//操作2
			printf("%d\n",a.sum(y)-a.sum(x-1));//如上“查询”章所说
	}
	//a.print();//调试
	return 0;
}
