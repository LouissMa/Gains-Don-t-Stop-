#include <bits/stdc++.h>
using namespace std;
// 这里不需要 define int long long，因为计算主要靠 double
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);

int main()
{
    SPEED;
    int n;
    cin >> n;
    // 使用 double 或 long double 防止精度丢失
    vector<double> a(n);
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    
    // 关键步骤：从小到大排序
    // 这样最小的数会最先被合成（被开根号最多次），最大的数最后被合成
    sort(a.begin(), a.end());
    
    // 取出第一个数作为初始结果
    double ans = a[0];
    
    // 从第二个数开始，依次与前面的结果合成
    for(int i = 1; i < n; i++)
    {
        ans = sqrt(ans * a[i]);
    }
    
    // 输出结果，保留足够的小数位（虽然题目默认cout通常也够，但fixed更稳）
    cout << fixed << setprecision(10) << ans << endl;
    
    return 0;
}