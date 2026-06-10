#include<bits/stdc++.h>
using namespace std;
struct node {
	int c , v ;
}a[200001];
int d[200001] , idx ;
int n , m , k;
bool cmp ( node xx , node yy ) {
	return xx.v > yy.v ; 
}
int main(){
	cin >> n >> k >> m ;
	for ( int i = 1 ;i <= n ; i ++ ) {
		cin >> a[i].c >> a[i].v ;
	}
	sort( a+1 , a+n+1 , cmp ) ;
	long long sum = 0 ;
	for ( int i = 1 ;i <= n ; i ++ ) {
		if ( d[a[i].c] != 0 ) {
			if ( k > m -idx ) {
				sum += a[i].v ;
				k -- ;
			}
		}else{
			sum += a[i].v ;
			k -- ;
			d[a[i].c]=1 ;
			idx ++ ;
		}
		if (k<=0)break ;
	}
	cout << sum ;
	return 0;
}
