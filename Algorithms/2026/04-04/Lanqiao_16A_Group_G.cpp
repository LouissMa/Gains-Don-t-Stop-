#include <iostream>
#include <cmath>
#include <algorithm>
 
using namespace std;
 
typedef pair<double, double> pdd;
 
const int N = 1e5 + 5;
const double pi = acos(-1);
 
pdd seg[N];
 
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++){
        double x, y, r;
        cin >> x >> y >> r;
        double alpha = atan(y / x);
        double delta = asin(r / sqrt(pow(x, 2) + pow(y, 2)));
        seg[i] = {alpha - delta, alpha + delta};
    }
    sort(seg + 1, seg + n + 1);
    double tot = 0;
    double l = 0, r = 0;
    for (int i = 1; i <= n; i ++){
        if (seg[i].first > r) {
            tot += r - l;
            l = seg[i].first, r = seg[i].second;
        }else if (seg[i].second > r) r = seg[i].second;
    }
    tot += r - l;
    printf("%.3f", 1 - (2 * tot / pi));
    return 0;
}