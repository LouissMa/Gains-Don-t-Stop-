//https://www.luogu.com.cn/problem/CF296B
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int mod=1e9+7;
int f[N][2][2];
void test(){
    int n;cin>>n;
    string s1,s2;cin>>s1>>s2;
    s1=' '+s1;
    s2=' '+s2;
    f[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=1;j++){
            for(int k=0;k<=1;k++){
                for(char c1='0';c1<='9';c1++){
                    if(c1==s1[i]||s1[i]=='?')
                    for(char c2='0';c2<='9';c2++){
                        if(c2==s2[i]||s2[i]=='?'){
                            f[i][j|c1<c2][k|c1>c2]=(f[i][j|c1<c2][k|c1>c2]+f[i-1][j][k])%mod;
                        }
                    }
                }
            }
        }
    }
    cout<<f[n][1][1]<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int T=1;
    while(T--){
        test();
    }
    return 0;
}