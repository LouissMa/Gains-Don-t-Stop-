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
int n,d;
vector<int> parent,a;
vector<vector<int>> ver;
void solve() 
{
    cin>>n>>d;
    int sum = n * (n - 1) / 2;
    if(d > sum)
    {
        cout<<"NO\n";
        return;
    }
    parent.resize(n);
    a.assign(n,1);
    for(int i=n-1,j=1;i > j;i--)
    {
        if(i - j < sum - d)
        {
            --a[i];
            ++a[j];
            sum -= i - j;
            if(a[j] == (1 << j))j++;
        }
        else
        {
            --a[i];
            ++a[i - (sum - d)];
            sum = d;
            break;
        }
    }
    if(sum != d)
    {
        cout<<"NO\n";
        return;
    }
    ver.assign(n, {});
    ver[0].push_back(0);
    int num = 1;
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<a[i];j++)
        {
            ver[i].push_back(num);
            parent[num] = ver[i-1][j/2];
            ++num;
        }
    }
    cout<<"YES\n";
    for(int i=1;i<n;i++) cout<<parent[i] + 1<<" \n"[i == n-1];
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