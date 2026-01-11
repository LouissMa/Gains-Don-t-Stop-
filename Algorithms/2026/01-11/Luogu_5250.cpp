#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int m;
    cin >> m;
    set<int> s;
    while(m--)
    {
        int op;
        cin >> op;
        if(op == 1)
        {
            int x;
            cin >> x;
            if(s.count(x))
            {
                cout << "Already Exist\n";
            }
            else
            {
                s.insert(x);
            }
        }
        else
        {
            int x;
            cin >> x;
            if(s.size() == 0)
            {
                cout << "Empty\n";
            }
            else if(s.count(x))
            {
                cout << x << "\n";
                s.erase(x);
            }
            else
            {
                auto it = s.lower_bound(x);
                if(it != s.end())
                {
                    int res = *it;  // 第一个 >= x 的元素
                    
                    // 检查是否存在小于x的元素
                    int best_val = res;
                    
                    // 同时检查前一个元素（如果存在）
                    if(it != s.begin())
                    {
                        auto prev_it = it;
                        prev_it--;
                        int res2 = *prev_it;  // 最大的 < x 的元素
                        
                        // 比较哪个更接近x
                        if(abs(res2 - x) <= abs(res - x))
                        {
                            best_val = res2;
                        }
                    }
                    
                    cout << best_val << "\n";
                    s.erase(best_val);
                }
                else
                {
                    // 所有元素都小于x，取最大值（最后一个元素）
                    auto last_it = s.end();
                    last_it--;
                    cout << *last_it << "\n";
                    s.erase(last_it);
                }
            }
        }
    }
    return 0;
}