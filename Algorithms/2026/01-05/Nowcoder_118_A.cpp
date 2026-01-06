#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int a,b;
    cin>>a>>b;
    if(a==b) cout<<"Draw";
    else if((a==1&&b==2)||(a==0&&b==1)||(a==2&&b==0)) cout<<"Hongwins";
    else cout<<"chengwins";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tt=1;
    //cin>>tt;
    while (tt--)  solve();
    return 0;
}