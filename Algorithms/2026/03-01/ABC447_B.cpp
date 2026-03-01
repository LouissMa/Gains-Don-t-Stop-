#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    string s;
    cin>>s;
    int cnt[26] {};
    for (auto c : s) {
        cnt[c - 'a']++;
    }
    
    int maxx = *std::max_element(cnt, cnt + 26);
    string t;
    for(auto c : s)
    {
        if(cnt[c - 'a'] != maxx) t += c;
    }
    cout<<t<<endl;
    return 0;
}