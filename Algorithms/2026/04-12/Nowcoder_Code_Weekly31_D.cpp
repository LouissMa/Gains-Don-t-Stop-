#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
struct work {
    int id;     
    int arrive;  
    int rem;
    bool operator<(const work& o) const {
        if (rem != o.rem)
        {
            return rem> o.rem;
        }
        return id > o.id;
    }
};

signed main()
{
    SPEED;
    
    int n;
    cin>>n;
    vector<int> t(n + 1);
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++) 
    {
        cin >> t[i] >> s[i];
    }
    
    vector<int> ans(n + 1);
    priority_queue<work> pq;
    int cur = 0;
    for (int i = 1; i <= n; i++) 
    {
        int next = t[i];
        while (!pq.empty() && cur < next) 
        {
            work cur_work = pq.top();
            pq.pop();
            int ava = next - cur;
            
            if (cur_work.rem <= ava) 
            {
                cur += cur_work.rem;
                ans[cur_work.id] = cur;
            } 
            else {
                cur_work.rem -= ava;
                cur = next;
                pq.push(cur_work); 
            }
        }
        cur = max(cur, next);
        pq.push({i, t[i], s[i]});
    }
    while (!pq.empty()) 
    {
        work curr = pq.top();
        pq.pop();
        cur += curr.rem;
        ans[curr.id] = cur;
    }
    for (int i = 1; i <= n; i++) 
    {
        cout << ans[i]<<" ";
    }
    cout << "\n";
    return 0;
}