#include <bits/stdc++.h>
using namespace std;
int cnt[10],cur[10];
string s;
bool check(int c){
	int i,d,x,dd,c5=0,c9=0;
	d=min(cur[0],c);
	x=c-d;
	cur[0]-=d;
	for(i=9;i>-1;i--)
	{
		dd=min(cur[i],d);
		cur[i]-=dd;
		d-=dd;
	}
	if(cur[1]<x*2)return 0;
	cur[1]-=x*2;
	for(i=0;i<10;i++)
	{
		if(i<=5)c5+=cur[i];
		c9+=cur[i];
	}
	if(c5<c||c9<c*2)return 0;
	return 1;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T,n,i,l,r,mid;
	for(cin>>T;T>0;T--)
	{
		cin>>n>>s;
		for(i=0;i<10;i++)cnt[i]=0;
		for(i=0;i<n;i++)cnt[s[i]-'0']++;
		l=0;
		r=n/4+1;
		while(r-l>1)
		{
			mid=(l+r)/2;
			for(i=0;i<10;i++)cur[i]=cnt[i];
			if(check(mid))l=mid;
			else r=mid;
		}
		cout<<l<<'\n';
	}
	return 0;
}