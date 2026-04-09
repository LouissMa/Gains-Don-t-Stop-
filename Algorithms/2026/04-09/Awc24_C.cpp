#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int h,w;
    cin>>h>>w;
    vector<string> g(h);
    for(int i=0;i<h;i++) cin>>g[i];
    set<PII> s;
    for(int i=0;i<h;i++)
    {
        vector<int> l(26,-1);
        vector<int> c;
        for(int j=0;j<w;j++)
        {
            int idx = g[i][j] - 'a';
            if(l[idx] != -1) l[idx] = -2;
            else l[idx] = j;
        }
        for(int j=0;j<26;j++)
        {
            if(l[j] != -1 && l[j] != -2) c.push_back(l[j]);
        }
        char ch;
        for(int id = 0;id < c.size();id ++)
        {
            ch = g[i][c[id]];
            bool ok = true;
            for(int k=0;k<h;k++)
            {
                if(k == i) continue;
                if(g[k][c[id]] == ch)
                {
                    ok = false;
                    break;
                }
            }
            if(ok) s.insert({i,c[id]});
        }
    }
    string ans = "";
    for(const auto &p : s)
    {
        ans += g[p.first][p.second];
    }
    cout<<ans<<endl;
    return 0;
}