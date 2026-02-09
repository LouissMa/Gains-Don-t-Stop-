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
    vector<int> a(n);
    unordered_map<int,int> cnt;
    int mx = 0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        cnt[a[i]] ++;
        mx = max(mx,a[i]);
    }
    if(cnt[mx] % 2 == 1){    
            for(int i = 0; i < n; i++){
                // 只有最大值能赢(1)，其他人输(0)
                if(a[i] == mx) cout << '1';
                else cout << '0';  
            }
        }
        // 如果最大值的数量是偶数
        else {
            for(int i = 0; i < n; i++){
                // 最大值互相抵消必输(0)，利用最大值消灭强敌后，其他人能赢(1)
                if(a[i] == mx) cout << '0';
                else cout << '1'; 
            }
        }
    cout<<'\n';
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