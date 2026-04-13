/*
Problem: CBC
Contest: Tokio Marine & Nichido Fire Insurance Programming Contest 2025 (AtCoder Beginner Contest 402)
URL: https://atcoder.jp/contests/abc402/tasks/abc402_a
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
    string n;
    for(int i=0;i<s.size();i++)
    {
        if(s[i] >= 'A' && s[i] <= 'Z') cout<<s[i];
    }
    cout<<endl;
    return 0;
}