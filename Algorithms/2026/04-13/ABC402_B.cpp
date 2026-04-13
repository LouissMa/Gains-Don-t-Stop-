/*
Problem: Restaurant QueueRestaurant Queue
Contest: Tokio Marine & Nichido Fire Insurance Programming Contest 2025 (AtCoder Beginner Contest 402)
URL: https://atcoder.jp/contests/abc402/tasks/abc402_b
Memory Limit: 1024 MB
Time Limit: 2000 ms

Description:
Paste problem statement here
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int q;
    cin>>q;
    queue<int> h;
    while(q--)
    {
        int op;
        cin>>op;
        if(op == 1)
        {
            int x;
            cin>>x;
            h.push(x);
        }
        else
        {
            cout<<h.front()<<endl;
            h.pop();
        }
    }
    return 0;
}