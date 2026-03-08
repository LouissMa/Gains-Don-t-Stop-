#include <bits/stdc++.h>
using namespace std;
struct apos{
	int a;
	int pos;
	friend bool operator<(apos a,apos b){
		return a.a<b.a;
	}
}ap[300000];
int inv[300000],b[300000];
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n,q,k,i;
	cin>>n>>q;
	for(i=0;i<n;i++)
	{
		cin>>ap[i].a;
		ap[i].pos=i;
	}
	sort(ap,ap+n);
	for(i=0;i<n;i++)inv[ap[i].pos]=i;
	for(;q>0;q--)
	{
		cin>>k;
		for(i=0;i<k;i++)
		{
			cin>>b[i];
			b[i]=inv[b[i]-1];
		}
		sort(b,b+k);
		for(i=0;i<k&&b[i]==i;i++);
		cout<<ap[i].a<<'\n';
	}
	return 0;
}