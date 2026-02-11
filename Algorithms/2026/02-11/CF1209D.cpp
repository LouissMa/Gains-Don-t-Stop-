#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> graph[100005];
bool vis[100005];

signed main() {
    int n, k; cin >> k >> n;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> comps;
    int happy=0;

    for (int i = 1; i <= k; i++) {
        if (vis[i]) continue;

        vector<int> to_visit;
        to_visit.push_back(i);
        int c = 0;
        vis[i]=1;

        while (! to_visit.empty()) {
            int node = to_visit.back();
            to_visit.pop_back();

            c++;

            for (auto x : graph[node]) {
                if (! vis[x]) {
                    vis[x]=1;
                    to_visit.push_back(x);
                }
            }
        }

        happy += c-1;
    }

    cout << n-happy << "\n";
}