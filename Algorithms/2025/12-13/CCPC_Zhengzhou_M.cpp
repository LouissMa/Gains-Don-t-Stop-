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
    string s;
    cin>>s;
    int n = s.size();
    int L=  0;
    while(L<n && s[L] == '0') L++;
    vector<int> A;
    int len = 0;
    for(int i=1,j=1;i+1<n;i++)
    {
        j = max(j,i+1);
        while(j < n && s[j] == '0') j++;
        if(L > i+1) continue;
        int l =i-L;
        int r = n - j;
        if(l < 0) l = 0;
        if(l != r)
        {
            int cur = max(l,r);
            if(len < cur)
            {
                A.clear();
                len = cur;
            }
            if(len == cur) A.push_back(i);
        }
        else
        {
            if(L + 1 < i && s[L+1] != s[j+1])
            {
                int cur = l-1;
                if(len < cur)
                {
                    A.clear();
                    len = cur;
                }
                if(len == cur) A.push_back(i);
            }
        }
    }
    if(len == 0)
    {
        cout<<0<<endl;
        return;
    }
    string AA = "";
    for(int w=0;w<A.size();w++)
    {
        int p = A[w];
        string ans = "";
        for(int i=1;i<n;i++)
        {
            int l = p-i;
            int r = n-i;
            int x = 0;
            if(l >= 0)x ^= (s[l] - '0');
            if(r > p) x ^= (s[r] - '0');
            ans += char(x + '0');
        }
        while (ans.back() == '0') ans.pop_back();
        reverse(ans.begin(), ans.end());
        if(w == 0) AA = ans;
        int ok = 0;
        for(int j=0;j<ans.size();j++)
        {
            if(ans[j] > AA[j])
            {
                ok = 1;
                break;
            }
            if(ans[j] < AA[j]) break;
        }
        if(ok == 1) AA = ans;
    }
    cout<<AA<<endl;
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