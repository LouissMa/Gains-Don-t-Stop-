/*
Problem: Problem Title
Contest: Contest Name
URL: URL
Memory Limit: 1024 MB
Time Limit: 2000 ms

Description:
Paste problem statement here
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

void solve() 
{
    int n,x,y;
    cin>>n>>x>>y;
    string s;
    cin>>s;
    if(x<0)x=-x;
	if(y<0)y=-y;
	for(int i=n-1;i>-1;i--)
	{
		if(s[i]=='8')
		{
			x--;
			y--;
		}
		else
		{
			if(x>y)x--;
			else y--;
		}
	}
	if(x<=0&&y<=0)cout<<"YES\n";
	else cout<<"NO\n";
}

signed main() 
{
    SPEED;
    int t = 1;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}