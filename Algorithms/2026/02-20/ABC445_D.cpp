#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int H, W, N;
    cin >> H >> W >> N;
    vector<int> h(N), w(N);
    for (int i = 0; i < N; i++)
    {
        cin >> h[i] >> w[i];
    }
    vector<int> ph(N), pw(N);
    iota(ph.begin(), ph.end(), 0);
    sort(ph.begin(), ph.end(), [&](int i, int j){
        return h[i] > h[j];
    });
    iota(pw.begin(), pw.end(), 0);
    sort(pw.begin(), pw.end(), [&](int i, int j){
        return w[i] > w[j];
    });
    vector<int> vis(N), x(N), y(N);
    int i = 0, j = 0;
    while (i < N)
    {
        if (h[ph[i]] == H)
        {
            int u = ph[i];
            vis[u] = 1;
            x[u] = 1;
            y[u] = W - w[u] + 1;
            W -= w[u];
        }
        else
        {
            assert(w[pw[j]] == W);
            int u = pw[j];
            vis[u] = 1; 
            x[u] = H - h[u] + 1; // 贴着空地的最下边放
            y[u] = 1;   // 贴着空地的最左边放
            H -= h[u];  // 空地总高度减去这块巧克力的高度
        }
        while (i < N && vis[ph[i]] == 1) i++;
        while (j < N && vis[pw[j]] == 1) j++;
    }
    for (int k = 0; k < N; k++) // 修改循环变量名以避免混淆
    {
        cout << x[k] << " " << y[k] << endl;
    }
    return 0;
}