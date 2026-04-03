#include <iostream>
#include <algorithm>
 
using namespace std;
 
const int N = 1e3 + 5;
 
int a[N], b[N], c[N];
 
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1; i <= n; i ++) cin >> b[i];
    for (int i = 1; i <= n; i ++) cin >> c[i];
    int m;
    cin >> m;
    int x = 1, y = 1, z = 1;
    int ans = 0;
    while (m --){
        int x1, x2, x3;
        cin >> x1 >> x2 >> x3;
        x += x1, y += x2, z += x3;
        while (x > n) x -= n;
        while (y > n) y -= n;
        while (z > n) z -= n;
        if (a[x] == b[y] && a[x] == c[z] || a[x] + 1 == b[y] && b[y] + 1 == c[z]){
            ans += 200;
            continue;
        }
        int t[] = {a[x], b[y], c[z]};
        sort(t, t + 3);
        if (t[0] == t[1] || t[1] == t[2] || t[0] + 1 == t[1] && t[1] + 1 == t[2])
            ans += 100;
    }
    cout << ans << endl;
    return 0;
}