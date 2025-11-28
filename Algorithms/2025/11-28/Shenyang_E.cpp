#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int a[100005],book[100005][10],b[100005];
signed main() {
	cin.tie(0) -> ios::sync_with_stdio(false);
	cout.tie(0)-> ios::sync_with_stdio(false);
	int t;cin>>t;
	while(t--){
		int n,ans=0;cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++){
			int x=a[i];b[i]=0;
			while(x){
				b[i]=max(b[i],x%10);
				x/=10;
			}
		}
		for(int i=1;i<=9;i++){book[0][0]=1;
			for(int j=1,last=-1,sum=0;j<=n;j++){
				if(b[j]>i){
					sum=0;
					for(int k=0;k<i;k++)
						book[j][k]=0;
					book[j][0]=1;
					last=-1;
					continue;
				}sum+=a[j];
				if(b[j]==i)
					last=j-1;
				if(last!=-1)ans+=book[last][sum%i];
				for(int k=0;k<i;k++)book[j][k]=book[j-1][k];
				book[j][sum%i]++;
			}//cout<<ans<<endl;
		}cout<<ans<<'\n';
	}
	return 0;
}