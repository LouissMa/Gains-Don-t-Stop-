#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

const int N = 2e5+10;
int n,p[N],ans = 0x3f3f3f3f,cnt;

int find(int x){
    ++cnt;
	return (p[x]==x?x:find(p[x]));
}
signed main()
{
    SPEED;
    cin>>n;
    for(int i=1;i<=n;i++) p[i] = i;
    for(int i=1;i<=n;cnt = 0,i++)
    {
        int t;
        cin>>t;
        find(t) == i?ans = min(ans,cnt):p[i] = t;
    }
    cout<<ans<<endl;
    return 0;
}