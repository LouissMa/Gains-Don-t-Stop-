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
    #define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
    typedef pair<long long, long long> pii; // 显式使用 long long
    
    long long get_rev(long long n) // 显式使用 long long
    {
        long long res = 0;
        while(n)
        {
            res = res * 10 + n % 10;
            n /= 10;
        }
        return res;
    }
    
    void solve() 
    {
        long long l, r; // 显式使用 long long
        cin >> l >> r;
        long long maxx = get_rev(r);
        for(long long p = 10; p <= r * 10; p *= 10)
        {
            long long cur = (r / p) * p - 1;
            if(cur < l) break;
            maxx = max(maxx, get_rev(cur));
        }
        std::cout << maxx << "\n"; // 使用 std::cout 消除歧义
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