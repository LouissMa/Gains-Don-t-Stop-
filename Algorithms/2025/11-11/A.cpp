#include<bits/stdc++.h>
using namespace std;
void test()
{
    int n;
    cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a.begin()+1,a.end());
    for(int i=2;i<n;i+=2)
    {
        if(a[i]!=a[i+1])
        {
            cout<<"NO"<<'\n';
            return;
        }
    }
    cout<<"Yes"<<'\n';
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    int T=1;
    cin>>T;
    while(T--){
        test();
    }
    return 0;
}