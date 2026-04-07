#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

int gcd(int a,int b)
{
    return b == 0 ? a : gcd(b,a % b);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}
int lcm(int a, int b, int c) {
    return lcm(lcm(a,b), c);
}

bool check(vector<int>& b,vector<int>& v)
{
    if(v.size() < 3) return false;
    int d1 = gcd(gcd(b[0],b[1]),b[2]);
    int d2 = gcd(gcd(v[0],v[1]),v[2]);
    if(d1 != d2) return d1 < d2;
    for(int i=0;i<3;i++)
    {
        if(b[i] != v[i]) return b[i] > v[i];
    }
    return false;
}
signed main()
{
    SPEED;
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    map<int, vector<int>> mp;
    for (auto u : a) {
    // 经典 O(sqrt(u)) 找约数算法
        for (int i = 1; i <= u / i; i++) {
            if (u % i == 0) { 
                mp[i].push_back(u); // i 是 u 的约数，把宝石 u 放进 i 号桶
                if (i != u / i) mp[u / i].push_back(u); // u/i 也是 u 的约数，放进 u/i 号桶
            }
        }
    }
    vector<int> b(3,-1);
    for(auto [u,v] : mp)
    {
        sort(v.begin(),v.end());
        if(b[0] == -1 || check(b,v))
        {
            for(int i=0;i<3;i++) b[i] = v[i];
        }
    }
    for(int i=0;i<3;i++) cout<<b[i]<<" \n"[i == 2];
    return 0;
}