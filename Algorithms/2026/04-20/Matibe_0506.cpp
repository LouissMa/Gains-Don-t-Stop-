#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);

const int N = 3010;
int a[N];
int pre_less[N]; // 记录位置 i 左边比它小的数的个数
int suf_less[N]; // 记录位置 i 右边比它小的数的个数

signed main()
{
    SPEED;
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    // 1. 预处理 pre_less 和 suf_less
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j < i; j++)
        {
            if(a[j] < a[i]) pre_less[i]++;
        }
        for(int j = i + 1; j <= n; j++)
        {
            if(a[j] < a[i]) suf_less[i]++;
        }
    }
    
    int ans = 0;
    
    // 2. 枚举 w 和 e 对子
    for(int w = 1; w <= n; w++)
    {
        for(int e = w + 1; e <= n; e++)
        {
            // 如果发现了两道美味度相同的菜
            if(a[w] == a[e])
            {
                // w 决定了左边 q 的选择，e 决定了右边 r 的选择
                // 乘起来就是这对 (w, e) 构成的合法四元组数量
                ans = (ans + pre_less[w] * suf_less[e]) % 10007;
            }
        }
    }
    
    cout << ans << endl;
    return 0;
}