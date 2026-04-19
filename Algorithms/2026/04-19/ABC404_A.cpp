/*
Problem: Not Found
Contest: AtCoder Beginner Contest 404
URL: https://atcoder.jp/contests/abc404/tasks/abc404_a
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
    string s;
    cin>>s;
    set<char> st;
    for(auto i : s)
    {
        st.insert(i);
    }
    for(char i='a';i<='z';i++)
    {
        if(!st.count(i))
        {
            cout<<i<<endl;
            return 0;
        }
    }
    return 0;
}