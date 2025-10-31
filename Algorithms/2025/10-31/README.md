# 🧠 2025-10-31 算法练习总结

## 📅 今日练习
- 题目来源：Codeforces Round 1062 (Div. 4)
- 完成题目：A, B, C, D, G
- 难度范围：800 ~ 1400
- 代码文件：
  - [A.cpp](./A.cpp)
  - [B.cpp](./B.cpp)
  - [C.cpp](./C.cpp)
  - [D.cpp](./D.cpp)
  - [jianglyG.cpp](./jianglyG.cpp)

---


## 🧩 今日收获
理解了G - Mukhammadali and the Smooth Array（Codeforces Round 1062 (Div. 4)）的正确做法，起初我想复杂了，具体题解看：10.31G讲解。
起初代码：
"""
/*
Problem: Problem Title
Contest: Contest Name
URL: URL
Memory Limit: 1024 MB
Time Limit: 2000 ms

Description:
Paste problem statement here
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

void solve() 
{
    int n;
    cin>>n;
    vector<int> a(n+1),c(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>c[i];
    vector<int> dp(n+1);
    int ans = 1e18;
    bool ok = false;
    for(int i=1;i<n;i++)
    {
        if(a[i] > a[i+1])
        {
            ok = true;
            break;
        }
    }
    if(!ok)
    {
        cout<<0<<"\n";
        return;
    }
    vector<bool> st(n+1,false);
    for(int i=2;i<=n;i++)
    {
        if(a[i-1] > a[i])
        {
            if(st[i-1])
            {
               dp[i] = dp[i-1] + c[i];
               st[i] = true;
               a[i] = a[i-1];
            }
            else
            {   if(i-2 >= 1 && a[i] < a[i-2])
                {
                    dp[i] = dp[i-1] + c[i];
                    a[i] = a[i-1];
                    st[i] = true;
                    continue;
                }
                dp[i] = min(dp[i-1] + c[i],dp[i-1] + c[i-1]);
                if(dp[i] == dp[i-1] + c[i-1]) 
                {
                    st[i] = false;
                    if(i-1 == 1) a[i-1] = a[i];
                    if(i-2>=1)
                    {
                        a[i-1] = a[i-2];
                    }
                }
                else 
                {
                    st[i] = true;
                    a[i] = a[i-1];
                }
            }
        }
        else dp[i] = dp[i-1];
    }
    cout<<dp[n]<<"\n";
}

signed main() 
{
    SPEED;
    int t = 1;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}
"""
---



---

## 🧭 明日目标
继续前进！

---

🪶 *“代码不只是解题，更是雕刻思维的刀锋。”*
