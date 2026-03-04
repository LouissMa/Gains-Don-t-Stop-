//Stop learning useless algorithms, go and solve some problems, learn how to use binary search.
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
void solve(){
    int n,q;
    cin>>n>>q;
    vector<int>a(n+2),pre(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];    
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+(a[i]==a[i+1]);
    for(int i=1;i<=q;i++){
        int l,r;cin>>l>>r;
        cout<<pre[r-1]-pre[l-1]<<endl;
    }
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    int T=1;//cin>>T;
    while(T--) solve();
    return 0;
}