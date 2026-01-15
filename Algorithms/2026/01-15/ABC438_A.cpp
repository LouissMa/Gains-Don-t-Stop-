#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int d,f;
	cin>>d>>f;
	f--;
	cout<<(f+7-d%7)%7+1<<'\n';
	return 0;
}