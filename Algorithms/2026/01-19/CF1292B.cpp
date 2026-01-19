#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
const int LIMIT = 2e16 + 7;
vector<int> x,y;

int dist(int x1,int y1,int x2,int y2)
{
    return abs(x1-x2) + abs(y1-y2);
}
signed main()
{
    SPEED;
    int x0,y0,ax,ay,bx,by;
    int xs,ys,t;
    cin>>x0>>y0>>ax>>ay>>bx>>by>>xs>>ys>>t;
    x.push_back(x0);
    y.push_back(y0);
    while(true){
        int cx = x.back();
        int cy = y.back();
        if(cx > LIMIT || cy > LIMIT) break;
        int nx = ax * cx + bx;
        int ny = ay * cy + by;
        x.push_back(nx);
        y.push_back(ny);
    }   
    int n = x.size();
    int ans =0;
    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
            int seg_dist = dist(x[i],y[i],x[j],y[j]);
            int dist_to_start = dist(x[i],y[i],xs,ys);
            int dist_to_end = dist(x[j],y[j],xs,ys);
            int tot = seg_dist + min(dist_to_start,dist_to_end);
            if(tot <= t) ans = max(ans,j - i + 1);
        }
    }
    cout<<ans<<endl;
    return 0;
}