#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5, INF = 0x3f3f3f3f;

vector<int> mul(vector<int>&a, int b){
    vector<int> c; int t=0;
    for(int i=0; i<a.size()||t; i++){
        if(i<a.size()) t += a[i]*b;
        c.push_back(t%10);
        t/=10;
    }
    while(c.size()>1 && c.back()==0) c.pop_back();
    return c;
}
int main(){
    int n; string d; cin>>n>>d;
    int id = d.find('.');
    int x = d.size() - id - 1;
    d.erase(id, 1);// d = d * 10 ^ x

    vector<int> a;
    for (auto u : d) a.push_back(u - '0');
    reverse(a.begin(), a.end());// 初始反转，后续就一直是反的
    for(int i=1; i<=n; i++) a = mul(a, 2);
    
    string ans = "";
    a[x] += a[x - 1] >= 5; // 四舍五入
    for (int i = x, t = 0; i < a.size() || t; i++) {
        if (i < a.size()) t += a[i];
        ans += t % 10 + '0';
        t /= 10;
    }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
    return 0;
}
