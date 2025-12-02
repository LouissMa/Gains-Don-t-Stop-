#include <bits/stdc++.h>
using namespace std;

using ui = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(l);i>=(r);--i)
#define repn(i,n)  for(int i=0;i<(n);++i)
#define sizc(x) ((int)x.size())
#define allc(x) x.begin(),x.end()
#define fir first
#define sec second

int xl,yl,xr,yr;
int X1,Y1,X2,Y2;
bool chk1(int x,int y1,int y2){
    if(y1>y2)swap(y1,y2);
    if(X2<x || X1>x)return 0;
    if(X1==X2){
        return X1==x && max(Y1,y1) <= min(Y2,y2);
    }
    // Y1 + (Y2-Y1) * (x-X1) / (X2-X1)
    int pos=Y1*(X2-X1)+(Y2-Y1)*(x-X1);
    return y1*(X2-X1)<=pos && pos<=y2*(X2-X1);
}
bool chk2(int x,int y){
    return min(xl,xr) <= x && x <= max(xl,xr)
        && min(yl,yr) <= y && y <= max(yl,yr);
}
void solve(){
    cin>>xl>>yl>>xr>>yr;
    cin>>X1>>Y1>>X2>>Y2;
    if(chk2(X1,Y1) || chk2(X2,Y2)){
        cout<<"STOP\n";
        return;
    }
    repn(_,2){
        if(X1>X2)swap(X1,X2),swap(Y1,Y2);
        if(chk1(xl,yl,yr) || chk1(xr,yl,yr)){
            cout<<"STOP\n";
            return;
        }
        swap(xl,yl),swap(xr,yr);
        swap(X1,Y1),swap(X2,Y2);
    }
    cout<<"OK\n";
}

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;cin>>T;
    while(T--)solve();
}
