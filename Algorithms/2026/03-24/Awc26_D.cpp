#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);

signed main()
{
    SPEED;
    int n, k;
    cin >> n >> k;
    map<int, int> diff; 
    
    for(int i = 1; i <= n; i++)
    {
        int l, r;
        cin >> l >> r;
        diff[l]++;     // 长度从 L 开始增加
        diff[r]--;     // 长度到 R 结束（注意这里是 r，不是 r+1）
    }
    
    int ans = 0;
    int current_coverage = 0; // 记录当前的涂漆厚度
    int last_pos = 0;         // 记录上一个关键点的位置
    
    // 遍历所有发生了涂漆变化的坐标点
    for(auto& [pos, change] : diff)
    {
        // 如果在到达当前坐标 pos 之前，前面那段的厚度是达标的 (>= k)
        if(current_coverage >= k)
        {
            // 那么加上这段达标区间的长度：当前坐标 - 上一个坐标
            ans += pos - last_pos; 
        }
        
        // 更新当前的厚度
        current_coverage += change;
        // 把当前坐标标记为下一段区间的起点
        last_pos = pos; 
    }
    
    cout << ans << "\n";
    return 0;
}