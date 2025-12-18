#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 510;
int n;
int a[N][N];

signed main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin>>n;
    for(int i=1;i<n;i++)
    {
    	for(int j = i+1;j<=n;j++)
    	{
    		cin>>a[i][j];
    		a[j][i] = a[i][j];
    	}
    }
    
    vector<int> sec;
    for(int i=1;i<=n;i++)
    {
    	vector<int> val;
    	for(int j = 1;j<=n;j++)
    	{
    		if(i!=j) val.push_back(a[i][j]);
    	}
    	
    	sort(val.rbegin(),val.rend());
    	sec.push_back(val[1]);
    }
    
    int res = *max_element(sec.begin(),sec.end());
    
    cout<<1<<endl;
    cout<<res<<endl;
    return 0;
}