#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;
struct State {
    int len, link;
    int next[26];
    State() {
        len = 0;
        link = -1;
        memset(next, -1, sizeof(next));
    }
};

struct SAM {
    vector<State> st;
    int sz, last;
    void init(int n) {
        st.clear();
        st.reserve(2 * n + 5);
        st.emplace_back();
        sz = 1;
        last = 0;
    }
    
    void extend(char c) {
        int cur = sz++;
        st.emplace_back();
        st[cur].len = st[last].len + 1;
        
        int p = last;
        int code = c - 'a';
        while (p != -1 && st[p].next[code] == -1) {
            st[p].next[code] = cur;
            p = st[p].link;
        }
        
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[code];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                while (p != -1 && st[p].next[code] == q) {
                    st[p].next[code] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
};

SAM sam;
vector<int> nodes;
vector<int> dp;

void solve() 
{
    string s;
    cin >> s;
    int n = s.length();
    sam.init(n);
    for (char c : s) {
        sam.extend(c);
    }
    
    int cnt = sam.sz;
    if ((int)nodes.size() < cnt) nodes.resize(cnt);
    if ((int)dp.size() < cnt) dp.resize(cnt);
    for (int i = 0; i < cnt; i++) nodes[i] = i;
    sort(nodes.begin(), nodes.begin() + cnt, [&](int a, int b) {
        return sam.st[a].len > sam.st[b].len;
    });
    for (int i = 0; i < cnt; i++) {
        int u = nodes[i];
        bool can_reach_losing = false;
        
        for (int c = 0; c < 26; c++) {
            if (sam.st[u].next[c] != -1) {
                int v = sam.st[u].next[c];
                if (dp[v] == 0) {
                    can_reach_losing = true;
                    break;
                }
            }
        }
        dp[u] = can_reach_losing ? 1 : 0;
    }
    if (dp[0]) cout << "Alice" << "\n";
    else cout << "Bob" << "\n";
}

signed main() 
{
    SPEED;
    int t = 1;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}