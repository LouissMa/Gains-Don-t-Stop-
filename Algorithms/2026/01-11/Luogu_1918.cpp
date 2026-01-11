#include<bits/stdc++.h>
using namespace std;
map<int,int> mp;//高级数组 第一个int---->x类型，第二个int---->y类型相当于 f(x)=y;
int main(){
	int n,m,x, q;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		mp[x]=i;//x--->i,x为瓶子数，i为位置 
	} 
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>q;
		cout<<mp[q]<<endl;//找不到默认对应为0，可以偷懒
//		mp.count(q);——>mp中q出现了几次；
		//if(mp.count(q) == 1) cout << mp[q] << endl;
		//else cout << 0 << endl; 这是不偷懒的方法
	} 
	return 0;
} 
