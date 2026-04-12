#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int x1,y1,z1,x2,y2,z2;
    cin>>x1>>y1>>z1>>x2>>y2>>z2;
    int k;
    cin>>k;
    int dx = abs(x1-x2);
    int dy = abs(y1-y2);
    int dz = abs(z1-z2);
    for(int i=0;i<k;i++)
    {
        if(dx == 0 && dy == 0 && dz == 0) break;
        if(dx >= dy && dx >= dz) dx --;
        else if(dy >= dx && dy >= dz) dy --;
        else dz --;
    }
    cout<<dx * dx + dy * dy + dz * dz<<endl;
    return 0;

}