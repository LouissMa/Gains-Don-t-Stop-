#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin>>n;

    vector<vector<int>> unlocks(n + 1); 
    vector<bool> learned(n + 1, false);
    queue<int> q;
    
    int ans = 0;
    for(int i=1; i<=n; i++)
    {
        int u, v;
        cin >> u >> v;

        if (u == 0 && v == 0) 
        {
            if (!learned[i]) { 
                learned[i] = true;
                q.push(i);
                ans++;
            }
        } else 
        { 
            unlocks[u].push_back(i);
            unlocks[v].push_back(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : unlocks[u]) {

            if (!learned[v]) {
                learned[v] = true;
                q.push(v); 
                ans++;
            }
        }
    }

    cout << ans << endl;
    return 0;
}