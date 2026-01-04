#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N];

void solve(){
    int n = 0;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    // 1. 排序，方便找最大值和最小值
    sort(a + 1, a + n + 1);
    
    // 情况一：最大值比最小值大 1 (存在唯一主颜色)
    // a[1] 是 min, a[n] 是 max
    if(a[1] == a[n] - 1){
        int cnt = 0; 
        int k = a[n]; // k 就是那个“最大颜色数量 M”
        
        // 统计有多少人回答了 M-1 (即 a[1])
        for(int i = 1; i <= n; i++){
            if(a[i] == a[1]) cnt++;
        }
        
        // 核心判断：回答 M-1 的人数，必须等于 M 本身
        // 比如 M=3，那就必须有3个人回答2。
        if(cnt == k) cout << "Other" << "\n"; // 合法
        else cout << "Lie" << "\n";
    }
    // 情况二：所有人的回答都一样
    else if(a[1] == a[n]){
        // 子情况 2.1: 所有人同色 (看到 n-1 个同色)
        if(a[1] == n - 1) cout << "Other" << "\n";
        // 子情况 2.2: 至少两种颜色并列第一 (2 * M <= n)
        else if(a[1] * 2 <= n) cout << "Other" << "\n";
        // 否则就是说谎
        else cout << "Lie" << "\n";
    }
    // 情况三：差值超过 1 (比如有人说 2，有人说 4)，绝对不可能
    else cout << "Lie" << endl;
}

int main(){
    int t = 0;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}