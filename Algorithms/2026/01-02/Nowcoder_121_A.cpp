#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
string s = "Kato_Shoko";
char ss[N];
int main(){
    int n = 0;
    cin>>n;
    int ans = 0;
    map<int, int> mp;
    for(int i = 0; i<n; i++){
        cin>>ss[i];
        if(ss[i]=='_') mp['_']++;
        else if(ss[i]=='K') mp['K']++;
        else if(ss[i]=='a') mp['a']++;
        else if(ss[i]=='t') mp['t']++;
        else if(ss[i]=='o') mp['o']++;
        else if(ss[i]=='S') mp['S']++;
        else if(ss[i]=='h') mp['h']++;
        else if(ss[i]=='k') mp['k']++;
    }
    if(!mp.count('_')||!mp.count('K')||!mp.count('a')||!mp.count('t')||!mp.count('o')||!mp.count('S')||!mp.count('h')||!mp.count('k')){
        cout<<"NO"<<"\n";
        return 0;
    }
    if(mp['o']<3){
        cout<<"NO"<<"\n";
        return 0;
    }
    ans+=(n-10);
    cout<<"YES"<<" "<<ans;
    return 0;
}